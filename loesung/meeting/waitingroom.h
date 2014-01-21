/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

#ifndef __waitingroom_include__
#define __waitingroom_include__

#include "object/queue.h"
#include "thread/customer.h"

class Customer; // Forward declaration

class Waitingroom : public Queue
{
private:
    Waitingroom(const Waitingroom &copy); // Verhindere Kopieren
public:
    Waitingroom() {}

	// Der Destruktor entfernt alle noch wartenden Prozesse von der Liste und weckt sie zudem auf.
	virtual ~Waitingroom ();

	// Mit dieser Methode kann der angegebene Prozess customer vorzeitig aus dem Wartezimmer entfernt werden.
	virtual void remove (Customer* customer);
};

#endif
