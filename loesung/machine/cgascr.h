#ifndef __screen_include__
#define __screen_include__

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/io_port.h"

class CGA_Screen
 {
private:
/* Hier muesst ihr selbst Code vervollstaendigen */ 

   CGA_Screen(const CGA_Screen &copy); // Verhindere Kopieren
public:
   CGA_Screen()
/* Hier muesst ihr selbst Code vervollstaendigen */ 
 {}

   // Diese Methode gibt das Zeichen c an der Position (x,y) mit dem angegebenen
   // Farbattribut attrib aus. Dabei gibt x die Spalte und y die Zeile der
   // gewünschten Position an, wobei gilt: 0<=x<=79 und 0<=y<=24. Die Position
   // (0,0) bezeichnet die linke obere Ecke des Bildschirms. Mit attrib lassen
   // sich Merkmale wie Hintergrundfarbe, Vordergrundfarbe und Blinken
   // festlegen.
   void show(int x, int y, char c, unsigned char attrib);

   // Diese Methode setzt den Cursor an die angegebene Position.
   void setpos(int x, int y);

   // Hiermit kann die aktuelle Position des Cursors von der Grafikkarte
   // abgefragt werden. x und y sind Referenzen und dienen als Ausgabeparameter.
   void getpos(int &x, int &y);

   // Mit dieser Methode kann eine Zeichenkette text ausgegeben werden, wobei an
   // der aktuellen Position des Cursors begonnen wird. Da die Zeichenkette
   // anders als sonst bei C üblich keine Nullterminierung zu enthalten braucht,
   // wird der Parameter length benötigt, der angeben muss, aus wievielen
   // Zeichen text besteht. Nach Abschluss der Ausgabe soll der Cursor hinter
   // dem zuletzt ausgegebenen Zeichen stehen. Der gesamte text soll einheitlich
   // mit den durch attrib gewählten Farben dargestellt werden.
   // Wenn bis zum Ende der Zeile nicht mehr genügend Platz ist, soll die
   // Ausgabe auf der folgenden Zeile fortgesetzt werden. Sobald die letzte
   // Bildschirmzeile gefüllt ist, soll der gesamte Bildschirmbereich um eine
   // Zeile nach oben geschoben werden. Dadurch verschwindet die erste Zeile.
   // Dafür kann nun die letzte Zeile erst gelöscht und dann die Ausgabe dort
   // fortgesetzt werden.
   // Ein Zeilenumbruch muss auch erfolgen, wann immer das Zeichen '\n' im
   // auszugebenen Text enthalten ist.
   void print(const char *text, int length, unsigned char attrib);
 };

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#endif

