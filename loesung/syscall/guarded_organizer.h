/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ O R G A N I Z E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#ifndef __Guarded_Organizer_include__
#define __Guarded_Organizer_include__

#include "syscall/thread.h"
#include "thread/organizer.h"
        
class Guarded_Organizer 
 : public Organizer
 {
private:
      Guarded_Organizer (const Guarded_Organizer &copy); // Verhindere Kopieren
public:
      Guarded_Organizer () {}

    /* Mit dieser Methode kann sich der laufende Prozess selbst blockieren. Er
    gibt also den Prozessor an den nächsten lauffähigen Prozess ab. Außerdem
    vermerkt er, auf welches Ereignis (in welchem Wartezimmer) er nun wartet. */
    void block (Thread& customer, Waitingroom& waitingroom);

    /* Mit dieser Methode kann ein schlafender Prozess geweckt, also wieder auf
    die Ready-Liste gesetzt werden. Dabei sollte auch markiert werden, dass der
    Prozess nun auf kein Ereignis mehr wartet.*/
    void wakeup (Thread& customer);

    /* Mit dieser Methode kann ein Prozess einen anderen (that) beenden. Wenn der
    Prozess that auf der Ready-Liste steht, kann die kill-Methode des Schedulers
    verwendet werden. Wartet er dagegen auf ein Ereignis, so muss er von dessen
    Liste (also aus dem Wartezimmer) heruntergenommen werden.*/
    void kill (Thread& that);
 };

#endif
