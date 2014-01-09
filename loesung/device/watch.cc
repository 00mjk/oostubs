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
#include "syscall/guarded_scheduler.h"

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream kout;
extern Guarded_Scheduler scheduler;

void Watch::windup() {
	plugbox.assign(Plugbox::timer, *this);
	pic.allow(PIC::timer);
}

bool Watch::prologue() { return true; }

void Watch:: epilogue() {
	// sorgt zusammen mit der initialisierung der Watch dafür,
	// dass etwa jede Sekunde eine Ausgabe gemacht wird.
	if (++test % 1000 == 0)
	//	kout << test << endl;
		scheduler.Scheduler::resume();
}
