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

static int compare(int a, int b) {
  if (a == b)
    return 0;
  return a > b ? -1 : 1;
}

void Enemy::action ()
 {
  Guarded_Buzzer buzzer;
  for (;;) {
    sem_display.p();
    kout.show(x, y, ' ', 0x0f);
    sem_display.v();
    sem_player.p();
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
    sem_player.v();
    sem_display.p();
    kout.show(x, y, 233, 0x0f);
    sem_display.v();
    buzzer.set(40);
    buzzer.sleep();
  }
 }
