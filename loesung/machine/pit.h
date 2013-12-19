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
};

#endif
