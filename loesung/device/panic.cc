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
#include "machine/cpu.h"

extern CGA_Stream kout;
extern CPU cpu;

bool Panic::prologue() {
	kout << endl << "PANIC! System will halt." << endl;
	cpu.disable_int();
	for (;;) {}
	return false;
}
