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
#include "machine/cpu.h"
#include "guard/guard.h"

extern CPU cpu;
extern Guard guard;

void Scheduler::ready(Entrant &that) {
  ready_list.enqueue(&that);
}

void Scheduler::schedule() {
  Chain *head;
  while (!(head = ready_list.dequeue())) {
    // Ist das so richtig?
    guard.leave();
    cpu.idle();
    guard.enter();
  }
  Dispatcher::dispatch(*static_cast<Entrant *>(head));
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

