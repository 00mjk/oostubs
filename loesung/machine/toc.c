/* $Id: toc.c 956 2008-10-19 22:24:23Z hsc $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Struktur toc dient dazu, bei einem Koroutinenwechsel die Werte der    */
/* nicht-fluechtigen Register zu sichern.                                    */
/* Beim GNU C Compiler sind eax, ecx und edx fluechtige Register, die bei    */
/* Funktionsaufrufen und somit auch bei einem Koroutinenwechsel keine        */
/* spaeter noch benoetigten Werte haben duerfen. Daher muss in der Struktur  */
/* toc auch kein Platz fuer sie bereitgestellt werden.                       */
/*****************************************************************************/

#include "machine/toc.h"

// TOC_SETTLE: bereitet den Kontext der Koroutine fuer den ersten
//             Aufruf vor.
void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*),
		 void* object)
 {
/* Hier muesst ihr selbst Code vervollstaendigen */          
 }
