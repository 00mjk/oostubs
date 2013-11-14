/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Klasse von Objekten, die in der Lage sind, Unterbrechungen zu behandeln.  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

class Gate : public Chain {
	bool _queued;

public:
	Gate() : _queued(false) {}	

	// Prolog der Unterbrechungsbehandlung. Ein Rückgabewert true zeigt an,
	// dass der zugehörige Epilog ausgeführt werden soll.
	virtual bool prologue() = 0;

	// Epilogue der Unterbrechungsbehandlung.
	virtual void epilogue() {}

	// Speichert, ob das jeweilige Objekt sich gerade in einer
	// Epilog-Warteschlange befindet.
	void queued (bool q) { _queued = q; }

	// Methode zum Abfragen, ob sich das jeweilige Objekte gerade in einer
	// Epilog-Warteschlange befindet.
	bool queued () { return _queued; }
};

#endif
