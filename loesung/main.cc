/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "device/cgastr.h"
#include "user/appl.h"
#include "machine/pic.h"
#include "machine/cpu.h"
#include "device/panic.h"
#include "machine/plugbox.h"
#include "device/keyboard.h"
#include "guard/guard.h"
#include "syscall/guarded_scheduler.h"
//#include "thread/scheduler.h"
#include "device/watch.h"

#include "user/print_rep.h"

CGA_Stream kout;
PIC pic;
CPU cpu;
Panic panic;
Plugbox plugbox;
Keyboard keyboard;
Guard guard;
//Scheduler scheduler;
Guarded_Scheduler scheduler;

// Löst etwa jede Millisekunde einen Timerinterrupt aus.
// Zusammen mit dem Testprolog der Watch
// wird so etwa jede Sekunde eine Ausgabe gemacht.
Watch watch(1000);

int main()
{
	// Die gelegentlich auftretenden Panics werden durch den Interrupt #39 (LPTR1) ausgelöst
	// http://ess.cs.tu-dortmund.de/Teaching/WS2013/BSB/Aufgaben/fehler.html#interrupt_7_39
	// Krücke: ein Gate namens LPTR wird an die entsprechende Stelle in der Plugbox geschaltet

  // Interrupts eintragen.
  keyboard.plugin();
  watch.windup();

  //Interrupts erlauben
  cpu.enable_int();

  kout.clear();

//  static char stack_app[4096];
//  Application app(stack_app + sizeof(stack_app));

//  static char stack_a[4096];
//  Print_Rep a(stack_a + sizeof(stack_a),'a');

//  scheduler.go(a);

  for(;;) ;

  return 0;
}
