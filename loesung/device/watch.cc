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
#include "meeting/bellringer.h"
#include "cgastr.h"
#include "syscall/guarded_organizer.h"

extern Bellringer bellringer;
extern Plugbox plugbox;
extern PIC pic;
extern Guarded_Organizer organizer;

void Watch::windup() {
	plugbox.assign(Plugbox::timer, *this);
	pic.allow(PIC::timer);
}

bool Watch::prologue() {
  // Loese alle 20ms einen Epilog aus.
  return ++test % 20 == 0;
}

void Watch::epilogue() {
  // Glocken laeuten.
  bellringer.check();
  // Wechsel den Thread.
  organizer.Organizer::resume();
}
