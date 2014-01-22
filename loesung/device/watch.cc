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

bool Watch::prologue() {
  // Loese alle 20ms einen Epilog aus.
  return ++test % 20 == 0;
}

void Watch::epilogue() {
  // Wechsel den Thread.
  scheduler.Scheduler::resume();
}
