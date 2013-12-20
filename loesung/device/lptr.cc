/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L P T R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Durcker Unterbrechungsbehandlung.                                         */
/*****************************************************************************/

#include "lptr.h"
#include "device/cgastr.h"
#include "guard/secure.h"

extern CGA_Stream kout;


bool LPTR::prologue() {
	return true;
}

void LPTR::epilogue() {
	kout << "Druckerinterrupt (#39) aufgetreten." << endl;
}
