/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

/* INCLUDES */
#include "meeting/buzzer.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

extern Bellringer bellringer;
extern Guarded_Organizer organizer;

Buzzer::~Buzzer() {
  bellringer.cancel(this);
  while (Chain *elem = dequeue())
    organizer.Organizer::wakeup(*static_cast<Customer *>(elem));
}

void Buzzer::ring() {
  while (Chain *elem = dequeue())
    organizer.Organizer::wakeup(*static_cast<Customer *>(elem));
}

void Buzzer::set(int ms) {
  bellringer.cancel(this);
  bellringer.job(this, ms);
}

void Buzzer::sleep() {
  if (wait() > 0) {
    Customer *customer = static_cast<Customer *>(organizer.active());
    enqueue(customer);
    organizer.Organizer::block(*customer, *this);
  }
}
