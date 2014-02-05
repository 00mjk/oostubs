/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                K R O Z                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Globale Daten fuer das Spiel(tm).                                         */
/*****************************************************************************/

#ifndef __kroz_include__
#define __kroz_include__

#include "syscall/thread.h"
#include "user/enemy.h"
#include "user/statusbar.h"
#include "user/map.h"
#include "user/player_handler.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"


class Kroz : public Thread {
 private:
  Kroz (const Kroz &copy);

 public:

  Kroz(void *tos) : Thread(tos) {}

  void action ();

  void printReadyScreen();

  void printWelcomeScreen();

  void printInstructionsScreen();

  void printVictoryScreen();

  void transform(char *text, char c1, char c2, int dim);

  void transform(char *text, char c1, char c2, char c3, char c4, char c5, char c6, char c7, int dim);
};

#endif
