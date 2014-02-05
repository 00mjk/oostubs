#include "player_handler.h"
#include "syscall/guarded_semaphore.h"
#include "machine/key.h"
#include "map.h"
#include "statusbar.h"
#include "syscall/guarded_buzzer.h"

static void slay(int x, int y) {
  if (map.get(x, y) == Map::WALL_DESTRUCTIBLE) {
    map.set(x, y, 0);
    kout.show(x, y, ' ', 0x0f);
  }
}

void Player_Handler::movement(Key key) {
  sem_player.p();

  // Kollisionsabfrage
  int scancode = key.scancode();
  if (scancode == Key::scan::up && map.notBlocked(player_x,player_y-1))
    --player_y; 
  else if (scancode == Key::scan::down && map.notBlocked(player_x,player_y+1))
    ++player_y;
  else if (scancode == Key::scan::left && map.notBlocked(player_x-1,player_y))
    --player_x;
  else if (scancode == Key::scan::right && map.notBlocked(player_x+1,player_y))
    ++player_x;
  else if (key.ascii() == 'w') {
    slay(player_x, player_y-1);
    showWhip(player_x, player_y-1,UP);
    slay(player_x-1, player_y);
    showWhip(player_x-1, player_y,LEFT);
    slay(player_x, player_y+1);
    showWhip(player_x, player_y+1,DOWN);
    slay(player_x+1, player_y);
    showWhip(player_x+1, player_y,RIGHT);
  }

  // Debugausgaben
  //kout.setpos(0,24);
  //kout << "x = " << player_x << " y = " << player_y << " ";
  //kout.flush();

  // Ereignisabfrage: Schätze sammeln etc
  switch(map.get(player_x,player_y)) {
  case Map::TREASURE:
    status.inc_treasure();
    map.set(player_x,player_y,Map::EMPTY);
    break;
  case Map::PORTAL:
    // Partie beenden
    
    break;
  }
  sem_player.v();
}

void Player_Handler::showWhip(int x, int y, int whipDirection) {
  Guarded_Buzzer buzzer;
  if (map.get(x,y) == Map::EMPTY) {
    switch(whipDirection) {
      case UP:
	kout.show(x,y, '|', 0x0F);
	kout.show(player_x, player_y, 234, 0x02);
	break;
      case DOWN:
	kout.show(x,y, '|', 0x0F);
	kout.show(player_x, player_y, 234, 0x02);
	break;
      case LEFT:
	kout.show(x,y, '-', 0x0F);
	kout.show(player_x, player_y, 234, 0x02);
	break;
      case RIGHT:
	kout.show(x,y, '-', 0x0F);
	kout.show(player_x, player_y, 234, 0x02);
	break;
    }
    buzzer.set(3);
    buzzer.sleep();
    kout.show(x,y, ' ',0x0F);
  }
}