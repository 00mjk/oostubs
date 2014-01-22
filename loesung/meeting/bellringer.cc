/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#include "meeting/bellringer.h"

void Bellringer::check() {
  // Total ineffizient.
  Chain *ptr = first();
  while (ptr) {
    Bell *bell = static_cast<Bell *>(ptr);
    ptr = bell->next;

    bell->tick();
    if (bell->run_down()) {
      bell->ring();
      remove(bell);
    }
  }
}

void Bellringer::job(Bell *bell, int ticks) {
  bell->wait(ticks);
  enqueue(bell);
}
