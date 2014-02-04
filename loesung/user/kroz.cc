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
#include "library/random.h"
#include "machine/io_port.h"

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Keyboard keyboard;

Guarded_Semaphore sem_display(1);

// Sekunden von der CMOS-Uhr holen.
static int getRTC() {
  IO_Port address(0x70);
  IO_Port data(0x71);
  address.outb(0);
  return data.inb();
}

Random r(getRTC());

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
  Enemy enemy1(stack_enemy1 + sizeof(stack_enemy1), r.number() % 78 + 1, r.number() % 23 + 1);
  static char stack_enemy2[4096];
  Enemy enemy2(stack_enemy2 + sizeof(stack_enemy2), r.number() % 78 + 1, r.number() % 23 + 1);
  static char stack_enemy3[4096];
  Enemy enemy3(stack_enemy3 + sizeof(stack_enemy3), r.number() % 78 + 1, r.number() % 23 + 1);
  static char stack_enemy4[4096];
  Enemy enemy4(stack_enemy4 + sizeof(stack_enemy4), r.number() % 78 + 1, r.number() % 23 + 1);
  static char stack_enemy5[4096];
  Enemy enemy5(stack_enemy5 + sizeof(stack_enemy5), r.number() % 78 + 1, r.number() % 23 + 1);

  printReadyScreen();

  organizer.ready(enemy1);
  organizer.ready(enemy2);
  organizer.ready(enemy3);
  organizer.ready(enemy4);
  organizer.ready(enemy5);

  for (;;) {
    sem_display.p();
    kout.show(player_x, player_y, 234, 0x02);
    sem_display.v();

    Key k = keyboard.getkey();
    sem_display.p();

    if (map.get(player_x,player_y) == Map::MONSTER)
      kout.show(player_x,player_y, 148,0x04);
    else
      kout.show(player_x, player_y, ' ', 0x0f);
    kout.flush();
    sem_display.v();

    player_handler.movement(k);
  }
 }

//Soll das Spiel erst beginnen lasssen, wenn der Spieler
//Zeit hatte sich das Level anzusehen.
void Kroz::printReadyScreen() {
  sem_display.p();
  kout.setpos(40,0);
  kout.show(player_x, player_y, 234, 0x02);
  kout.print("Taste 's' zum Starten druecken.",30,0x04);
  kout.flush();
  Key k = keyboard.getkey();
  while (k.ascii() != 's') {
    if(k.ascii() != 0)
       kout << k.ascii() << endl;
    k = keyboard.getkey();
  }
  for (int x = 40; x < 70; x++) {
    kout.show(x,0, 178, 0x0f);
  }

  
  sem_display.v();
}

