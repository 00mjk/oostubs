/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#include "watch.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "cgastr.h"

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream kout;

void Watch::windup() {
	plugbox.assign(Plugbox::timer, *this);
	pic.allow(PIC::timer);
}

bool Watch::prologue() { return true; }

void Watch:: epilogue() {
	// sorgt zusammen mit der initialisierung der Watch dafür,
	// dass etwa jede Sekunde eine Ausgabe gemacht wird.
	if (test++ % 18 == 0)
	kout << "timer: " << test << endl;
}
