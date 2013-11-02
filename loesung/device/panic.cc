/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#include "panic.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

void Panic::trigger() {
	kout << endl << "PANIC! System will halt." << endl;
}