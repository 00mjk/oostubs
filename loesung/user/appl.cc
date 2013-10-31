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
/* Hier muesst ihr selbst Code vervollstaendigen */         
         
/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
/* Hier muesst ihr selbst Code vervollstaendigen */ 
         
void Application::action ()
 {
Keyboard_Controller kctrl;
kctrl.set_led(1, true);
kctrl.set_repeat_rate(0x14, 0x03);
kout << endl;

	Key key;
	for(;;) {
		key = kctrl.key_hit();
		if (key.valid()) {
			kout << key.ascii();
			kout.flush();
		}
	}
 }
