#include "map.h"

#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"

extern CGA_Stream kout;
extern Guarded_Semaphore sem_display;

Map::Map() {
  // den äußeren Rand und die Statusleiste mit Wänden schützen
  for (int i = 0; i < 80; i++) {
    typemap[i][0] = WALL;
    typemap[i][24] = WALL;
  }
  for (int i = 0; i < 25; i++) {
    typemap[0][i] = WALL;
    typemap[79][i] = WALL;
  }
  typemap[10][10] = TREASURE;
  typemap[70][10] = TREASURE;
}

void Map::print() {
  sem_display.p();
  for (int x = 0; x < 80; x++) {
    for (int y = 0; y < 25; y++) {
      switch(typemap[x][y]) {
      case WALL:
	kout.show(x,y, 178, 0x0f);
	break;
      case TREASURE:
	kout.show(x,y, 48, 0x0E);
	break;
      }
    }
  }
  sem_display.v();
}

char Map::get(int x, int y) {
  if (0 <= x && x <= 79 && 0 <= y && y <= 24) {
    return typemap[x][y];
  }
  else return 0;
}


bool Map::notBlocked(int x, int y) {
  if (0 <= x && x <= 79 && 0 <= y && y <= 24) {
    if (typemap[x][y] != WALL) {
      return true;
    }
  }
  return false;
}
