/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#include "syscall/guarded_semaphore.h"
#include "guard/secure.h"

void Guarded_Semaphore::p() {
  Secure s;
  Semaphore::p();
}

void Guarded_Semaphore::v() {
  Secure s;
  Semaphore::v();
}
