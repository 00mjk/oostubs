/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#include "thread/scheduler.h"
#include "thread/entrant.h"

void Scheduler::ready(Entrant &that) {
  ready_list.enqueue(&that);
}

void Scheduler::schedule() {
  Entrant *head = static_cast<Entrant *>(ready_list.dequeue());
  Dispatcher::dispatch(*head);
}

void Scheduler::exit() {
  schedule();
}

void Scheduler::kill(Entrant &that) {
  ready_list.remove(&that);
}

void Scheduler::resume() {
  Entrant *active = static_cast<Entrant *>(Dispatcher::active());
  ready_list.enqueue(active);

  schedule();
}

