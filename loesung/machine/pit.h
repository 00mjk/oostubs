/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "io_port.h"

class PIT
 {
private:
    PIT(const PIT &copy); // Verhindere Kopieren
    int inter;
    IO_Port ctrl;
    IO_Port periodic;
public:
    PIT (int us) : inter(us), ctrl(0x43), periodic(0x40) {
      interval(us);
    }
    int interval () { return inter; }

    void interval(int us);

    /* Konstanten für die Benutzung des Steuerregisters */
    enum { counter0 = 0x00, counter1 = 0x01, counter2 = 0x10, readback = 0x11 };
    enum { latch = 0x0000, lower = 0x0100, higer = 0x1000, both = 0x1100 };
    enum { mod0 = 0x0000000, mod1 = 0x0010000, mod2 = 0x0100000,
	   mod3 = 0x0110000, mod4 = 0x1000000, mod5 = 0x1010000 };
    enum { bin = 0x00000000, bcd = 0x10000000 };
};

#endif
