/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine "Glocke" ist eine abstrakte Basisklasse, die das Ausloesen einer     */
/* Aktivitaet nach einer bestimmten Wartezeit erlaubt.                       */
/* Dazu besitzt sie einen Zaehler, der vom "Gloeckner" (Bellringer) ver-     */
/* waltet wird.                                                              */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"

class Bell : public Chain
 {
private:
    Bell(const Bell &copy); // Verhindere Kopieren

    int counter;
public:
    Bell() {}

    // Setzen bzw. Abfragen des Zählers.
    void wait (int value) { counter = value; }
    int wait () const { return counter; }
    // Dekremementiert den Zähler.
    void tick () { --counter; }
    // Liefert true, wenn die Zeit abgelaufen ist.
    bool run_down() { return counter <= 0; }
    // Wird vom Glöckner aufgerufen, wenn es an der Zeit ist.
    virtual void ring () = 0;
};

#endif
