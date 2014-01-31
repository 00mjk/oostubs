/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 E N E M Y                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein thread der einen Feind repraesentiert.                                */
/*****************************************************************************/

#ifndef __enemy_include__
#define __enemy_include__

#include "syscall/thread.h"

class Enemy : public Thread

 {
private:
    Enemy (const Enemy &copy); // Verhindere Kopieren

    int x, y;

public:
    Enemy(void *tos, int x, int y) : Thread(tos), x(x), y(y) {}

    void action ();
 };

#endif
