/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ O R G A N I Z E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#include "syscall/guarded_organizer.h"
#include "guard/secure.h"

void Guarded_Organizer::block (Thread& customer, Waitingroom& waitingroom) {
  Secure s;
  Organizer::block(customer, waitingroom);
}

void Guarded_Organizer::wakeup (Thread& customer) {
  Secure s;
  Organizer::wakeup(customer);
}

void Guarded_Organizer::kill (Thread& that) {
  Secure s;
  Organizer::kill(that);
}
