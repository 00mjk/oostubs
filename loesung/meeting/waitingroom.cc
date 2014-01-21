/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

#include "waitingroom.h"
#include "object/chain.h"
#include "thread/customer.h"
#include "thread/organizer.h"

extern Organizer organizer; //bzw durch einen Guarded_Organizer zu ersetzen

Waitingroom::~Waitingroom () {
  Chain* chain;
  Customer* customer;
  while ((chain = dequeue())) {
    // Der Organizer kümmert sich um das room-Feld.
    customer = static_cast<Customer*>(chain);
    organizer.wakeup(*customer);
  }
}

void Waitingroom::remove (Customer* customer) {
  Queue::remove(customer);
  organizer.wakeup(*customer);
}
