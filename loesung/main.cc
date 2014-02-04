/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */

#include "device/cgastr.h"
#include "device/panic.h"
#include "device/watch.h"
#include "guard/guard.h"
#include "machine/cpu.h"
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/kroz.h"


#include "object/chain.h"
#include "meeting/bell.h"
#include "meeting/buzzer.h"

CGA_Stream kout;
PIC pic;
CPU cpu;
Panic panic;
Plugbox plugbox;
Guard guard;
Guarded_Keyboard keyboard;
Guarded_Organizer organizer;
Bellringer bellringer;

// Löst etwa jede Millisekunde einen Timerinterrupt aus.
// Zusammen mit dem Testprolog der Watch
// wird so etwa jede Sekunde eine Ausgabe gemacht.
Watch watch(1000);

// Zum Testen ohne weitere Prozesse                                                                                                                                                                                                         
// Kann später weggeworfen werden                                                                                                                                                                                                           
void bellringer_test() {
  Buzzer b1, b2, b3, b4, b5;

  bellringer.job(&b1,100); // Leere Liste
  bellringer.job(&b2,50); // kleinstes Element
  bellringer.job(&b3,75); // mittleres Element
  bellringer.job(&b4,150); // größtes Element
  bellringer.job(&b5,125); // mittleres Element
  // erwartete Ausgabe "50\n25\n25\n25\n25"
  
  Chain* run = bellringer.first();
  while (run) {
    kout << static_cast<Bell*>(run)->wait() << endl;
    run = run->next;
  }

}


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

  static char stack_app[4096];
  Kroz kroz(stack_app + sizeof(stack_app));

  guard.enter();
  organizer.go(kroz);

  for(;;) ;

  return 0;
}
