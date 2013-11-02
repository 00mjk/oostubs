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
#include "device/cgastr.h"

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream kout;

Keyboard::Keyboard() {
	plugbox.assign(Plugbox::keyboard,*this);
	pic.allow(PIC::keyboard);
}

void Keyboard::trigger() {
	unsigned char character= key_hit().ascii();
	if (character != 0) {
		kout << ((char) character);
		kout.flush();
	}
}
