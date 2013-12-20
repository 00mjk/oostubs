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

#include "thread/entrant.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

class Thread : public Entrant
 {
private:
      Thread (const Thread &copy); // Verhindere Kopieren
public:
	Thread(void* tos) : Entrant(tos) {}
 };


#endif
