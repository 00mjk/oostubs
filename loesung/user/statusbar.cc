#include "statusbar.h"
#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"

extern CGA_Stream kout;
extern Guarded_Semaphore sem_display;

Statusbar::Statusbar() {
  treasure = 0;
  hits = 0;
  print();
}

void Statusbar::print() {
  sem_display.p();
  kout.setpos(0,0);
  kout << "Treasure: " << treasure << " Hits taken: " << hits;
  kout.flush();
  sem_display.v();
}

void Statusbar::inc_treasure() {
  treasure++;
  print();
}

void Statusbar::inc_hits() {
  hits++;
  print();
}
