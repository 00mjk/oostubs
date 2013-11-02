/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "plugbox.h"
#include "device/panic.h"

extern Panic panic;

Plugbox::Plugbox() {
	for (int i = 0; i < 64; i++) {
		gates[i] = &panic;
	}
}

void Plugbox::assign (unsigned int slot, Gate& gate) {
	gates[slot] = &gate;
}

Gate& Plugbox::report (unsigned int slot) {
	return *gates[slot];
}

