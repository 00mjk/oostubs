#include "player_handler.h"
#include "syscall/guarded_semaphore.h"
#include "machine/key.h"
#include "map.h"
#include "statusbar.h"

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
    slay(player_x-1, player_y);
    slay(player_x+1, player_y);
    slay(player_x, player_y+1);
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
