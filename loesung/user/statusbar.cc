#include "statusbar.h"
#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"
#include "map.h"

extern CGA_Stream kout;
extern Guarded_Semaphore sem_display;
extern Map map;

void Statusbar::init() {
  treasure = 0;
  hits = 0;
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
  if (treasure == map.getTreasure()) {
    printPortalMessage();
    map.setDone();
  }
  print();
}

void Statusbar::inc_hits() {
  hits++;
  print();
}

void Statusbar::printPortalMessage() {
  kout.setpos(40,0);
  kout.print("Auf zum Portal!",14,0x04);
  kout.flush();
}
