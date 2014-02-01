/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "user/loop.h"
#include "user/enemy.h"
#include "user/statusbar.h"
#include "user/map.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Keyboard keyboard;
Guarded_Semaphore sem_display(1);

int player_x = 10, player_y = 10;
Guarded_Semaphore sem_player(1);

Map map;
Statusbar status;

void Application::action ()
 {
   map.print();
   status.print();
  static char stack_enemy1[4096];
  Enemy enemy1(stack_enemy1 + sizeof(stack_enemy1), 70, 20);
  organizer.ready(enemy1);
  static char stack_enemy2[4096];
  Enemy enemy2(stack_enemy2 + sizeof(stack_enemy2), 10, 25);
  organizer.ready(enemy2);
  static char stack_enemy3[4096];
  Enemy enemy3(stack_enemy3 + sizeof(stack_enemy3), 50, 1);
  organizer.ready(enemy3);
  //static char stack_loop2[4096];
  //Loop loop2(stack_loop2 + sizeof(stack_loop2), 100);
  //scheduler.ready(loop2);

  for (;;) {
    sem_display.p();
    kout.show(player_x, player_y, 234, 0x0f);
    sem_display.v();

    Key k = keyboard.getkey();
    sem_display.p();
    if (k.ascii() != 0)
      kout << k.ascii();

    kout.show(player_x, player_y, ' ', 0x0f);
    kout.flush();
    sem_display.v();

    sem_player.p();
    if (k.scancode() == Key::scan::up)
      --player_y;
    else if (k.scancode() == Key::scan::down)
      ++player_y;
    else if (k.scancode() == Key::scan::left)
      --player_x;
    else if (k.scancode() == Key::scan::right)
      ++player_x;
    sem_player.v();
  }
 }
