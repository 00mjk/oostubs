/* $Id: toc.h 956 2008-10-19 22:24:23Z hsc $ */

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
/*                                                                           */
/* Achtung: Fuer den Zugriff auf die Elemente von struct toc aus einer       */
/* Assemblerfunktion heraus werden in der Datei toc.inc Namen fuer die       */
/* benoetigten Abstaende der einzelnen Elemente zum Anfang der Struktur      */
/* definiert. Damit dann auch auf die richtigen Elemente zugegriffen wird,   */
/* sollten sich die Angaben von toc.h und toc.inc exakt entsprechen.         */
/* Wer also toc.h aendert, muss auch toc.inc anpassen (und umgekehrt.)       */
/*****************************************************************************/

#ifndef __toc_include__
#define __toc_include__

// TOC: ("thread of control")
//
struct toc
 {
      void *ebx;
      void *esi;
      void *edi;
      void *ebp;
      void *esp;
 };

#endif

