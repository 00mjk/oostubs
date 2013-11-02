/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Adresse der  */
/* Behandlungsroutine fuer jeden Hardware-, Softwareinterrupt und jede       */
/* Prozessorexception festlegen.                                             */
/*****************************************************************************/

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "guard/gate.h"

class Plugbox
 {
private:
    Plugbox(const Plugbox &copy); // Verhindere Kopieren
    Gate* gates[64];
public:
    Plugbox ();

    void assign (unsigned int slot, Gate& gate);

    Gate& report (unsigned int slot);

    enum { timer = 32, keyboard = 33 };
 };

#endif
