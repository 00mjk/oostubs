/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#include "pic.h"

void PIC::allow (int interrupt_device) {
        if (interrupt_device < 8) {
                //vom ersten PIC verwaltet
                //bit mit der Nummer interrupt_device muss genullt werden
//                master_imr.outb( master_imr.inb() - (interrupt_device + 1) );
		master_imr.outb( master_imr.inb() & ~(1 << interrupt_device) );
        } else {
                //vom zweten PIC verwaltet
//                master_imr.outb( master_imr.inb() - (interrupt_device + 1 - 8) );
		master_imr.outb( master_imr.inb() & ~(1 << (interrupt_device - 8)) );
        }
}

void PIC::forbid (int interrupt_device){
        if (interrupt_device < 8) {
                //vom ersten PIC verwaltet
                //bit mit der Nummer interrupt_device muss gesetzt werden
                master_imr.outb( master_imr.inb() | (1 << interrupt_device) );
        } else {
                //vom zweten PIC verwaltet
                master_imr.outb( master_imr.inb() | (1 << (interrupt_device - 8)) );
        }
}
