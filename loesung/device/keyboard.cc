/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#include "keyboard.h"
#include "machine/plugbox.h"
#include "machine/pic.h"

extern Plugbox plugbox;
extern PIC pic;

Keyboard::Keyboard() : read_key(true), sem_key(0) {
}

void Keyboard::plugin() {
	plugbox.assign(Plugbox::keyboard,*this);
	pic.allow(PIC::keyboard);
}

bool Keyboard::prologue() {
	Key key = key_hit();
	if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
		reboot();
	}
        this->last_key = key;
        return true;
	return false;
}

void Keyboard::epilogue() {
  if (read_key) {
    this->read_key = false;
    sem_key.v();
  }
}

Key Keyboard::getkey() {
  sem_key.p();
  read_key = true;
  return last_key;
}
