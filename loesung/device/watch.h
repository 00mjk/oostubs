/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#ifndef __watch_include__
#define __watch_include__

/* INCLUDES */

#include "guard/gate.h"
#include "machine/pit.h"

class Watch : public Gate, public PIT
 {
private:
    Watch (const Watch &copy); // Verhindere Kopieren
    int test;
public:
    // WATCH: Initialisiert die Uhr.
    Watch (int us) : PIT (us), test(0)
    {}

    // WINDUP: "zieht die Uhr auf". Danach laeuft sie los und loest in
    //         regelmaessigen Abstaenden Unterbrechungen aus.
    void windup ();

    // PROLOGUE: Prologue der Uhrenunterbrechung
    bool prologue ();

    // EPILOGUE: Epilogue der Uhrenunterbrechung
    void epilogue ();
 };

#endif
