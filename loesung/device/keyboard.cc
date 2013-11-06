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
	Key key = key_hit();
	unsigned char character= key.ascii();
	if (character != 0) {
                kout.setpos(10, 10);
		kout << ((char) character);
		kout.flush();
	} else if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
		reboot();
	}
}
