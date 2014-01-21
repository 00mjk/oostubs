/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Thread, der auf ein Ereignis warten kann.                             */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "meeting/waitingroom.h"
#include "entrant.h"
#include "object/chain.h"

class Waitingroom;

class Customer : public Entrant {
private:
    Customer (const Customer &copy); // Verhindere Kopieren
    Waitingroom* room;
public:
	// Der Konstruktor leitet den Parameter tos an den Konstruktor der Basisklasse Entrant weiter.
	Customer (void* tos) : Entrant(tos) { room = 0; next = 0; }

	// Mit dieser Methode wird im Customer vermerkt, dass dieser derzeit im Waitingroom w auf ein
	// Ereignis wartet.
	void waiting_in (Waitingroom *w) { room = w; }

	// Hiermit kann abgefragt werden, in welchem Waitingroom Objekt der Customer eingetragen ist.
	// Ein Rückgabewert von 0 soll bedeuten, dass der Prozess auf überhaupt kein Ereignis wartet,
        // also entweder der aktuell laufende Prozess ist, auf der Ready-Liste des Schedulers steht,
        // bereits terminiert ist oder noch gar nicht beim Scheduler angemeldet wurde.
	Waitingroom* waiting_in () { return room; }
};

#endif
