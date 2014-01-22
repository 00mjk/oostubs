/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Liste, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#ifndef __Bellringer_include__
#define __Bellringer_include__

#include "object/list.h"
#include "meeting/bell.h"

class Bellringer : public List
{
private:
   Bellringer(const Bellringer &copy); // Verhindere Kopieren
public:
   Bellringer() {}

   // Prüft, ob Glocken zu läuten sind und tut es gegebenenfalls.
   void check ();
   // Die Glocke bell wird dem Glöckner überantwortet. Sie soll nach ticks Zeiteinheiten geläutet werden.
   void job (Bell *bell, int ticks);
   // Die Glocke bell soll nun doch nicht geläutet werden.
   void cancel (Bell *bell) { remove(bell); }
};

#endif
