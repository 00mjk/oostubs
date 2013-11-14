/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#ifndef __panic_include__
#define __panic_include__

/* INCLUDES */

#include "guard/gate.h"

class Panic : public Gate
 {
private:
    Panic (const Panic &copy); // Verhindere Kopieren
public:
    Panic () {}

    // Einfachste Form der Unterbrechungsbehandlung: Es wird eine Fehlermeldung
    // ausgegeben und der Prozessor angehalten.
    bool prologue();
 };

#endif

