/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             T H R E A D                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Benutzerschnittstelle eines Threads.                                      */
/*****************************************************************************/

#ifndef __thread_include__
#define __thread_include__

#include "thread/customer.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

class Thread : public Customer
 {
private:
      Thread (const Thread &copy); // Verhindere Kopieren
public:
	Thread(void* tos) : Customer(tos) {}
 };


#endif
