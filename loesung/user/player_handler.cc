#include "player_handler.h"
#include "syscall/guarded_semaphore.h"
#include "machine/key.h"
#include "map.h"

void Player_Handler::movement(unsigned char scancode) {
  sem_player.p();
  if (scancode == Key::scan::up && map.notBlocked(player_x,player_y-1))
    --player_y; 
  else if (scancode == Key::scan::down && map.notBlocked(player_x,player_y+1))
    ++player_y;
  else if (scancode == Key::scan::left && map.notBlocked(player_x-1,player_y))
    --player_x;
  else if (scancode == Key::scan::right && map.notBlocked(player_x+1,player_y))
    ++player_x;
  kout.setpos(0,24);
  kout << "x = " << player_x << " y = " << player_y << " ";
  kout.flush();
  sem_player.p();
}
