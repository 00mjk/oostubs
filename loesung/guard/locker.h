/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"
extern CGA_Stream kout;

class Locker
 {
private:
    Locker(const Locker &copy); // Verhindere Kopieren

    bool _is_locked;
public:
    // Initialisiert die Sperrvariable so, dass der kritische Abschnitt als
    // frei markiert wird.
    Locker() : _is_locked(false) {}

    // Diese Methode muss aufgerufen werden, wenn der kritische Abschnitt
    // betreten wird.
    void enter () { 
	    if (_is_locked)
		    kout << "Fehler: enter mehrfach aufgerufen" << endl;

	    _is_locked = true;
    }
    // Mit dieser Methode wird der kritische Abschnitt wieder verlassen.
    void retne () { _is_locked = false; }
    // Diese Methode gibt an, ob der kritische Abschnitt frei ist.
    bool avail () { return !_is_locked; }
 };

#endif
