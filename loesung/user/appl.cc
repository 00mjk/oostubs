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
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern Guarded_Organizer organizer;
extern Guarded_Keyboard keyboard;
Guarded_Semaphore sem_display(1);

void Application::action ()
 {
  kout << "Hello" << endl;

  static char stack_loop1[4096];
  Loop loop1(stack_loop1 + sizeof(stack_loop1), 10000);
  organizer.ready(loop1);
  //static char stack_loop2[4096];
  //Loop loop2(stack_loop2 + sizeof(stack_loop2), 100);
  //scheduler.ready(loop2);

  for (;;) {
    Key k = keyboard.getkey();
    sem_display.p();
    kout << k.ascii();
    sem_display.v();
  }
 }
