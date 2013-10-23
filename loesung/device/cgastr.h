/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C G A _ S T R E A M                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse CGA_Stream ermoeglicht die Ausgabe verschiedener Datentypen    */
/* als Zeichenketten auf dem CGA Bildschirm eines PCs.                       */
/* Fuer weitergehende Formatierung oder spezielle Effekte stehen die         */
/* Methoden der Klasse CGA_Screen zur Verfuegung.                            */
/*****************************************************************************/

#ifndef __cgastr_include__
#define __cgastr_include__

#include "object/o_stream.h"
#include "machine/cgascr.h"

class CGA_Stream : public O_Stream, public CGA_Screen
 {
private:
      CGA_Stream(CGA_Stream &copy); // Verhindere Kopieren

public:
  CGA_Stream() {}
  ~CGA_Stream() { flush(); }

  // Mit dieser Methode wird der Inhalt des Zeichenpuffers auf dem
  // CGA-Bildschirm ausgegeben.
  void flush();
 };

#endif
