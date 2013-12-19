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
	// Insgesamt wird quot = [19318 * us / 10000] berechnet
	int prod = 19318 * us;
	int quot = prod / 10000;
	int mod = prod % 10000;
	// runden
	if (mod > 5000) quot++;
	ctrl.outb(0x34);
	// niederwertiges Byte
	periodic.outb(quot);
	// höherwertiges Byte
	periodic.outb((quot >> 8) & 0xff);
	kout << (quot & 0xFFFF) << endl;
}
