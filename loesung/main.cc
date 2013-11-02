/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "device/cgastr.h"
#include "user/appl.h"
#include "machine/pic.h"
#include "machine/cpu.h"
#include "device/panic.h"

CGA_Stream kout;
PIC pic;
CPU cpu;
Panic panic;

int main()
{

  //Tastaturinterrupts erlauben
  pic.allow(PIC::keyboard);
  cpu.enable_int();

  Application app;
  app.action();

	for (;;);

  return 0;
}
