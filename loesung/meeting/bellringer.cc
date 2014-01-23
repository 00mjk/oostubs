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
  Bell* bell = static_cast<Bell *>(first());
  bell->tick();
  if (bell->run_down()) {
    bell->ring();
    remove(bell);
  }
}

void Bellringer::job(Bell *bell, int ticks) {
  Chain* run = first();
  Chain* pred = 0;
  Bell* run_bell;

  // gibt es eine offensichtliche einfachere Lösung?
  // echt unpraktisch keine doppelt verkettete Liste zu haben

  while (run) {
    run_bell = static_cast<Bell *>(run);
    if (run_bell->wait() > ticks) {
      // vor run einfügen
      bell->wait(ticks);
      if (pred) {
	insert_after(pred,bell);
      } else {
	insert_first(bell);
      }
      break;
    }
    ticks -= run_bell->wait();
    pred = run;
    run = run->next;    
  }
  if (!run) {
    // entweder die Liste war leer, oder bell muss am längsten warten
    // dann ist bell noch nicht eingefügt worden
    bell->wait(ticks);
    enqueue(bell);
  } else {
    // bell steht nicht als letztes bzw. einziges Element in der Liste
    while (run) {
      run_bell = static_cast<Bell *>(run);
      run_bell->wait(run_bell->wait() - ticks);
      run = run->next;
    }
  }
}
