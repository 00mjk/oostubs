/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 E N E M Y                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein thread der einen Feind repraesentiert.                                */
/*****************************************************************************/

/* INCLUDES */

#include "user/kroz.h"
#include "user/enemy.h"
#include "user/statusbar.h"
#include "user/map.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "device/keyboard.h"
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Semaphore sem_display;
extern Map map;

static int compare(int a, int b) {
  if (a == b)
    return 0;
  return a > b ? -1 : 1;
}

Enemy::Enemy(void *tos, int x, int y) : Thread(tos), x(x), y(y) {
  kout.show(x, y, 233, 0x04);
  map.set(x,y,Map::MONSTER);
}

void Enemy::action ()
 {
  Guarded_Buzzer buzzer;
  for (;;) {
    sem_display.p();
    kout.show(x, y, ' ', 0x0f);
    sem_display.v();

    move();

    sem_display.p();
    kout.show(x, y, 148, 0x04);
    sem_display.v();
    buzzer.set(20);
    buzzer.sleep();
    sem_display.p();
    kout.show(x, y, 153, 0x04);
    sem_display.v();
    buzzer.set(20);
    buzzer.sleep();
  }
 }

void Enemy::move() {
    sem_player.p();

    int x_old = x, y_old = y;
    bool hit = false;

    if ((x+y) % 2 == 0) {
      if (compare(x, player_x))
        x += compare(x, player_x);
      else
        y += compare(y, player_y);
    } else {
      if (compare(y, player_y))
        y += compare(y, player_y);
      else
        x += compare(x, player_x);
    }

    if (map.blockedForEnemy(x,y)) {
      if (map.get(x,y) == Map::MONSTER)
	hit = true;
      x = x_old;
      y = y_old;
    }

    map.set(x_old,y_old,Map::EMPTY);
    if (x == player_x && y == player_y) {
      status.inc_hits();
      hit = true;
    } else {
      map.set(x,y,Map::MONSTER);
    }

    sem_player.v();
    
    if (hit) {
      organizer.exit();
    }
}
