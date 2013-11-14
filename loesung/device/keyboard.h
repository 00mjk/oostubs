/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"

class Keyboard : public Gate, public Keyboard_Controller
{
private:
      unsigned char last_key;

      Keyboard (const Keyboard &copy); // Verhindere Kopieren
public:
      Keyboard();

      // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
      void plugin ();

      // Mit dieser Methode wird auf die Unterbrechungen durch die Tastatur
      // reagiert. Da bei jedem Tastendruck mehrere Unterbrechungen ausgelöst
      // werden, ist nicht in jedem Fall mit einem verwertbaren ASCII-Code zu
      // rechnen. Nur wenn die Methode key_hit der Basisklasse
      // Keyboard_Controller einen gültigen Key liefert, konnte ein
      // vollständiger Scancode ermittelt werden. Für "normale" Tasten
      // existiert dann auch ein ASCII-Code ungleich Null.
      // Falls Ctrl-Alt-Delete gedrückt wurde, soll ein Reboot ausgelöst
      // werden. Außerdem soll die Ausführung eines Epilogs angefordert werden.
      bool prologue ();
      
      // Hier wird das im Rahmen der Prolog-Behandlung ausgelesene Zeichen auf
      // dem Bildschirm mit Hilfe des globalen CGA_Stream Objekts kout
      // ausgegeben.
      void epilogue ();
 };

#endif
