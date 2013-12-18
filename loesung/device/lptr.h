/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L P T R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Durcker Unterbrechungsbehandlung.                                         */
/*****************************************************************************/

#ifndef __lptr_include__
#define __lptr_include__

/* INCLUDES */

#include "guard/gate.h"

class LPTR : public Gate
 {
private:
    LPTR (const LPTR &copy); // Verhindere Kopieren
public:
    LPTR () {}

    // Macht darauf aufmerksam, dass ein Druckerinterrupt aufgetreten ist.
    // Da wir keinen Drucker verwenden, sind diese Interrupts ungewollt.
    bool prologue();
 };

#endif

