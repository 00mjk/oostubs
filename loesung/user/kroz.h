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

#include "syscall/guarded_semaphore.h"

extern int player_x, player_y;
extern Guarded_Semaphore sem_player;

#endif
