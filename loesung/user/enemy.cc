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
#include "library/random.h"

#define abs(x) ((x) < 0 ? (-(x)) : (x))

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Semaphore sem_display;
extern Map map;
extern Random r;

static int compare(int a, int b) {
  if (a == b)
    return 0;
  return a > b ? -1 : 1;
}

static int sleeptime() {
  return 10 - ((r.number() % 10) - 5);
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
    buzzer.set(sleeptime());
    buzzer.sleep();
    sem_display.p();
    kout.show(x, y, 153, 0x04);
    sem_display.v();
    buzzer.set(sleeptime());
    buzzer.sleep();
  }
 }

void Enemy::move() {
    sem_player.p();

    int x_old = x, y_old = y;
    bool hit = false, wall = false;

    if (abs(x - player_x) < 15 && abs(y - player_y) < 15) {
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
    }

    if (map.blockedForEnemy(x,y)) {
      if (map.get(x,y) == Map::MONSTER)
	hit = true;
      x = x_old;
      y = y_old;
    }

    if (map.get(x,y) == Map::WALL_DESTRUCTIBLE) {
      wall = true;
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

    if (wall) {
      // Langsam die Wand fressen.
      Guarded_Buzzer sleep;
      kout.show(x_old, y_old, 147, 0x04);
      kout.show(x, y, 240, 0x06);
      sleep.set(50);
      sleep.sleep();
      kout.show(x, y, '-', 0x06);
      sleep.set(50);
      sleep.sleep();
      kout.show(x_old, y_old, ' ', 0x04);
    }
}
