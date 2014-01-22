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
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;

Waitingroom::~Waitingroom () {
  Customer* customer;
  while (Chain *chain = dequeue()) {
    // Der Organizer kümmert sich um das room-Feld.
    customer = static_cast<Customer*>(chain);
    organizer.Organizer::wakeup(*customer);
  }
}

void Waitingroom::remove (Customer* customer) {
  Queue::remove(customer);
  organizer.Organizer::wakeup(*customer);
}
