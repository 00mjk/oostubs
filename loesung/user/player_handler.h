#ifndef __PLAYER_HANDLER_H__
#define __PLAYER_HANDLER_H__

#include "syscall/guarded_semaphore.h"
#include "device/cgastr.h"
#include "statusbar.h"
#include "machine/key.h"
#include "map.h"

extern Guarded_Semaphore sem_player;
extern Guarded_Semaphore sem_display;
extern Statusbar status;
extern Map map;
extern int player_x, player_y;
extern CGA_Stream kout;

/*
  Soll die Kollisionsabfrage, das aufsammlen von Schätzen etc für
  den Spieler übernehmen. Kann eigentlich auch in einen Player-Prozess
  integriert werden.
 */
class Player_Handler {
 private:
  
 public:
  void movement(unsigned char scancode);
};

#endif
