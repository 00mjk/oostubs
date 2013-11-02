/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */

/* Hier muesst ihr selbst Code vervollstaendigen */ 
#include "device/cgastr.h"
#include "user/appl.h"
#include "machine/pic.h"
#include "machine/cpu.h"

CGA_Stream kout;

int main()
{

  //Tastaturinterrupts erlauben
  //PIC pic;
  //pic.allow(PIC::keyboard);
  //CPU cpu;
  //cpu.enable_int();

  Application app;
  app.action();

  return 0;
}
