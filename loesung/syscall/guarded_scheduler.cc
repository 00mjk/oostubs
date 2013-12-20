/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#include "guarded_scheduler.h"
#include "thread.h"
#include "guard/secure.h"
#include "thread/entrant.h"

void Guarded_Scheduler::ready (Thread& that) {
	Scheduler::ready(that);
}

void Guarded_Scheduler::exit () {
	Scheduler::exit();
}

void Guarded_Scheduler::kill (Thread& that) {
	Scheduler::kill(that);
}

void Guarded_Scheduler::resume () {
	Scheduler::resume();
}
