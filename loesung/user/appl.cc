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
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "device/keyboard.h"

/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
extern CPU cpu;
extern Keyboard keyboard;

void Application::action ()
 {

	 for (;;) {
		 cpu.disable_int();
		 if (keyboard.get_leds())
			cpu.enable_int();
		 kout.setpos(20, 20);
		 kout << "Hello";
		 kout.flush();
		 cpu.enable_int();
	 }

 }
