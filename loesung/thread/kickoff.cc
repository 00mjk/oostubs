/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Funktion zum Starten einer Koroutine.                                     */
/* Da diese Funktion nicht wirklich aufgerufen, sondern nur durch eine       */
/* geschickte Initialisierung des Stacks der Koroutine angesprungen wird,    */
/* darf sie nie terminieren. Anderenfalls wuerde ein sinnloser Wert als      */
/* Ruecksprungadresse interpretiert werden und der Rechner abstuerzen.       */
/*****************************************************************************/

#include "device/cgastr.h"
#include "thread/coroutine.h"
#include "guard/guard.h"

extern CGA_Stream kout;
extern Guard guard;

extern "C" void kickoff (Coroutine* object) {
  guard.leave();
  object->action();

  kout << "PANIC: kickoff returned!" << endl;
  for (;;) {}
}
