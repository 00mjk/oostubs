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
#include "statusbar.h"
#include "device/cgastr.h"

extern Statusbar status;
extern CGA_Stream kout;

class Enemy : public Thread

 {
private:
    Enemy (const Enemy &copy); // Verhindere Kopieren

    int x, y;

public:
    Enemy(void *tos, int x, int y) : Thread(tos), x(x), y(y) {
      kout.show(x, y, 233, 0x04);
    }

    void action ();
    
    void move();
 };

#endif
