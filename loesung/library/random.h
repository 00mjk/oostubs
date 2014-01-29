/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               R A N D O M                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#ifndef __random_include__
#define __random_include__

class Random
 {
private:
      Random(const Random &copy); // Verhindere Kopieren

private:
      unsigned long r0, r1, r2, r3, r4, r5, r6;
      unsigned long multiplier, addend, ic_state;

public:
      // KONSTRUKTOR: initialisiert den Zufallszahlengenerator
      Random (int seed);

      // NUMBER: liefert eine Zufallszahl
      int number ();
 };

#endif
