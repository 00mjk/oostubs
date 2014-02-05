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
#include "syscall/guarded_buzzer.h"
#include "library/random.h"
#include "machine/io_port.h"
#include <new>
#include "screen.h"

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

static char monsterbuffer[50][4096];
Enemy &createMonster(int i) {
  int x, y;
  do {
    x = r.number() % 78 + 1;
    y = r.number() % 23 + 1;
  } while (map.get(x, y) != Map::EMPTY);
  Enemy *m = new (monsterbuffer[i]) Enemy(monsterbuffer[i] + 4096, x, y);
  return *m;
}

void Kroz::action ()
 {
  printWelcomeScreen();
  printInstructionsScreen();
  
  map.print();
  status.print();

  sem_player.p();
  for (int i = 0; i != 30; ++i)
	  organizer.ready(createMonster(i));
  sem_player.v();

  printReadyScreen();

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

void Kroz::printWelcomeScreen() {
  for (int y = 0; y < 12; y++)
    transform(title[y], 219, 176, 68);
  for (int y = 0; y < 12; y++) {
    kout.setpos(6,y+1);
    kout.print(title[y],68,0x0F);
  }
  for (int y = 0; y < 5; y++)
    transform(subtitle[y], 177, 176, 62);
  for (int y = 0; y < 5; y++) {
    kout.setpos(9,y+16);
    kout.print(subtitle[y],62,0x0F);
  }
  
  kout.setpos(28,22);
  kout.print("PRESS ENTER TO CONTINUE",23,0xE);
  kout.flush();
  kout.setpos(90,30);
  Key k = keyboard.getkey();
  while (k.scancode() != Key::scan::enter) {
    k = keyboard.getkey();
  }
  kout.clear();
}

void Kroz::printInstructionsScreen() {
  
  kout.setpos(35,2);
  kout << "Anleitung" << endl;
  
  int x = 14;
  
  kout.setpos(x,6);
  kout << "*";
  kout.flush();
  kout.show(x+2, 6, 234, 0x02);
  kout.setpos(x+4,6);
  kout << "stellt die Spielfigur dar" << endl;
  
  kout.setpos(x,8);
  kout << "* Sammle alle Muenzen ";
  kout.flush();
  kout.show(x+22, 8, 48, 0x0E);
  
  kout.setpos(x,10);
  kout << "* Wenn du alle hast, lauf zum Portal ";
  kout.flush();
  kout.show(x+37,10, 79, 0x01);

  kout.setpos(x,12);
  kout << "* Lass dich dabei nicht von den Monstern   fressen ";
  kout.flush();
  kout.show(x+41,12, 148, 0x04);
  
  kout.setpos(x,14);
  kout << "* Die Waende   sind durch das Schwert ('w') zerstoerbar" << endl;
  kout.show(x+13,14,176, 0x06);
  
  kout.setpos(x,16);
  kout << "* ...wenn sie nicht zuvor von den Monstern verspeist wurden" << endl;
  
  kout.setpos(x,18);
  kout << "* Ein Druck auf 'r startet das Spiel neu" << endl;
 

  
  kout.setpos(28,22);
  kout.print("PRESS ENTER TO CONTINUE",23,0xE);
  kout.flush();
  kout.setpos(90,30);
  Key k = keyboard.getkey();
  while (k.scancode() != Key::scan::enter) {
    k = keyboard.getkey();
  }
  kout.clear();
}

void Kroz::printVictoryScreen() {
  for (int y = 0; y < 6; y++) {
    transform(score[y],223,205,186,201,200,187,188,42);
  }
  for (int y = 0; y < 6; y++) {
    kout.setpos(20,y+5);
    kout.print(score[y],42,0x04);
  }
  kout.setpos(29,22);
  kout.print("PRESS ENTER TO RESTART",22,0xE);
  kout.flush();
  kout.setpos(90,30);
  Key k = keyboard.getkey();
  while (k.scancode() != Key::scan::enter) {
    k = keyboard.getkey();
  }
  kout.clear();
}

void Kroz::transform(char *text, char c1, char c2, int dim) {
  for (int i = 0; i < dim; i++) {
    if (text[i] == '1')
      text[i] = c1;
    else if (text[i] == '0')
      text[i] = c2;
  }
}

void Kroz::transform(char *text, char c1, char c2, char c3, char c4, char c5, char c6, char c7, int dim) {
  for (int i = 0; i < dim; i++) {
    switch (text[i]) {
      case '1':
	text[i] = c1;
	break;
      case '2':
	text[i] = c2;
	break;
      case '3':
	text[i] = c3;
	break;
      case '4':
	text[i] = c4;
	break;
      case '5':
	text[i] = c5;
	break;
      case '6':
	text[i] = c6;
	break;
      case '7':
	text[i] = c7;
	break;
    }
  }
}
