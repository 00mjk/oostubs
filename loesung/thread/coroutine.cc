/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Koroutinenkonzepts.                                   */
/* Im Konstruktor wird der initiale Kontext der Koroutine eingerichtet.      */
/* Mit go() wird die erste Koroutine aktiviert. Alle weiteren Koroutinen-    */
/* wechsel sollten mit resume() erfolgen.                                    */
/* Um bei einem Koroutinenwechsel den Kontext sichern zu koennen, enthaelt   */
/* jedes Koroutinenobjekt eine Struktur toc, in dem die Werte der nicht-     */
/* fluechtigen Register gesichert werden koennen.                            */
/*****************************************************************************/

#include "thread/coroutine.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++ 
// entsprechen.
extern "C"
 {
   void toc_go (struct toc* regs);

   void toc_switch (struct toc* regs_now,
                    struct toc* reg_then);

   void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*),
                    void* object);

   void kickoff (void *object);
 }

Coroutine::Coroutine(void *tos) {
  toc_settle(&regs, tos, kickoff, this);
}

void Coroutine::go() {
  toc_go(&regs);
}

void Coroutine::resume(Coroutine &next) {
  toc_switch(&regs, &next.regs);
}
