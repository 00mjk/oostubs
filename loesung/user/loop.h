/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab.                                                         */
/*****************************************************************************/

#ifndef __loop_include__
#define __loop_include__

#include "syscall/thread.h"

class Loop : public Thread
 
 {
private:
    Loop (const Loop &copy); // Verhindere Kopieren

    int i;
    int max;

public:
    Loop(void *tos, int max) : Thread(tos), i(0), max(max) {}

    void action ();
 };

#endif
