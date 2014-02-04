#include "user/kroz.h"
#include "user/enemy.h"
#include "user/statusbar.h"
#include "user/map.h"
#include "user/player_handler.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Keyboard keyboard;

Guarded_Semaphore sem_display(1);

int player_x = 10, player_y = 10;
Guarded_Semaphore sem_player(1);
Player_Handler player_handler;
Map map;
Statusbar status;

void Kroz::action ()
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

    player_handler.movement(k.scancode());
  }
 }
