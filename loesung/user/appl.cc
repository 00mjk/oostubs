/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "user/loop.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "device/keyboard.h"
#include "guard/secure.h"
#include "thread/scheduler.h"

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern Scheduler scheduler;

void Application::action ()
 {
  static char stack_loop1[4096];
  Loop loop1(stack_loop1 + sizeof(stack_loop1));
  scheduler.ready(loop1);
  static char stack_loop2[4096];
  Loop loop2(stack_loop2 + sizeof(stack_loop2));
  scheduler.ready(loop2);

  for (;;) {
    {
      Secure s;
      kout << "Hello" << endl;
    }
    scheduler.resume();
  }
 }
