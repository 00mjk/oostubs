/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#include "meeting/semaphore.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;

void Semaphore::p() {
  if (counter > 0) {
    --counter;
  } else {
    Customer *customer = static_cast<Customer *>(organizer.active());
    enqueue(customer);
    organizer.Organizer::block(*customer, *this);
  }
}

void Semaphore::v() {
  if (Chain *elem = dequeue())
    organizer.Organizer::wakeup(*static_cast<Customer *>(elem));
  else
    ++counter;
}
