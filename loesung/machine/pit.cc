/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "pit.h"
#include "device/cgastr.h"

extern CGA_Stream kout;


void PIT::interval(int us) {
	// Insgesamt wird quot = [1000 * us / 838] berechnet
	int prod = 1000 * us;
	int quot = prod / 838;
	int mod = prod % 838;
	// runden
	if (mod > 419) quot++;
	ctrl.outb(0x34);
	// niederwertiges Byte
	periodic.outb(quot);
	// höherwertiges Byte
	periodic.outb((quot >> 8) & 0xff);
	kout << (quot & 0xFFFF) << endl;
}
