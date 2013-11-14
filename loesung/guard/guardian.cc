/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */
#include "device/cgastr.h"
#include "machine/plugbox.h"

/* FUNKTIONEN */

extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

extern Plugbox plugbox;

void guardian (unsigned int slot)
 {
        if (plugbox.report(slot).prologue())
		plugbox.report(slot).epilogue();
 }

