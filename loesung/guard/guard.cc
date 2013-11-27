/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/

#include "guard/guard.h"
#include "guard/gate.h"
#include "machine/cpu.h"
extern CPU cpu;

void Guard::leave () {
	if (avail())
		kout << "Fehler: leave mehrfach aufgerufen" << endl;

	for (;;) {
		cpu.disable_int();
		Gate *g = (Gate *)_q.dequeue();
		if (!g) {
			retne();
			cpu.enable_int();
			return;
		}
		g->queued(false);
		cpu.enable_int();

		g->epilogue();
	}
}

void Guard::relay (Gate* item) {
	// Item schon in der Queue.
	if (item->queued())
		return;

	if (!avail()) {
		item->queued(true);
		_q.enqueue(item);
		return;
	}

	item->epilogue();
}
