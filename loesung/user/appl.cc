/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
/* Hier muesst ihr selbst Code vervollstaendigen */         
         
/* GLOBALE VARIABLEN */

extern CGA_Stream kout;
/* Hier muesst ihr selbst Code vervollstaendigen */ 
         
void Application::action ()
 {
  const char str[] = "hello world hello world hello world hello world hello "
                     "world hello world hello world\n";
  kout.setpos(10, 10);
  for (int i = 0; i != 20; ++i) {
    kout.print(str, sizeof(str) - 1, 0x09);
    kout.print(str, sizeof(str) - 1, 0x0C);
    kout.print("          ", i%10, 0x0F);
  }
  kout << (void*)str << ' ' << (unsigned long)str << ' ' << -42 << endl;
  kout << bin << 42 << ' ' << oct << 42 << ' ' << dec << 42 << ' ' << hex << 42
       << endl;
  kout << bin << -1 << ' ' << oct << -1 << ' ' << dec << -1 << ' ' << hex << -1
       << endl;
  int x,y;
  kout.getpos(x, y);
  kout << x << ' ' << y;
 }
