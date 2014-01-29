/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               R A N D O M                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

/* INCLUDES */

#include "library/random.h"

// KONSTRUKTOR: initialisiert den Zufallszahlengenerator
Random::Random (int seed)
 {
   // "index" selects which random number generator - which multiplier
   int index = 69069;

   seed = (69607 + 8 * index) * seed + 12345;
   r0 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r1 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r2 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r3 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r4 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r5 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   r6 = (seed >> 8) & 0xffffff;
   seed = (69607 + 8 * index) * seed + 12345;
   ic_state = seed;
   multiplier = 100005 + 8*index;
   addend = 12345;
 }

// NUMBER: liefert eine Zufallszahl
int Random::number ()
 {   
   register int  t, s;

   t = ( ((r5 >> 7) | (r6 << 17)) ^
         ((r4 >> 1) | (r5 << 23)) ) & 0xffffff;
   r6 = r5;
   r5 = r4;
   r4 = r3;
   r3 = r2;
   r2 = r1;
   r1 = r0;
   r0 = t;
   s = ic_state * multiplier + addend;
   ic_state = s;
   return  t ^ ((s>>8)&0xffffff);
 };

