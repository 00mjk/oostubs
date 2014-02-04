#include "map.h"

#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"

extern CGA_Stream kout;
extern Guarded_Semaphore sem_display;

Map::Map() : numTreasure(0), done(false) {
  // den äußeren Rand und die Statusleiste mit Wänden schützen
  for (int i = 0; i < 80; i++) {
    typemap[i][0] = WALL;
    typemap[i][24] = WALL;
  }
  for (int i = 0; i < 25; i++) {
    typemap[0][i] = WALL;
    typemap[79][i] = WALL;
  }

  // Testkarte
  set(12,12,TREASURE);
  set(70,10,TREASURE);

  typemap[20][10] = WALL;
  typemap[20][11] = WALL;
  typemap[20][12] = WALL;
  typemap[20][13] = WALL;
  typemap[20][14] = WALL;
  typemap[20][15] = WALL;
  typemap[20][16] = WALL;
  typemap[20][17] = WALL;

  typemap[40][40] = PORTAL;
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
      case PORTAL:
	kout.show(x,y, 79, 0x01);
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


void Map::set(int x, int y, char type) {
  if (0 <= x && x <= 79 && 0 <= y && y <= 24) {
    if (type == TREASURE)
      numTreasure++;
    typemap[x][y] = type;
  }
}

bool Map::notBlocked(int x, int y) {
  if (0 <= x && x <= 79 && 0 <= y && y <= 24) {
    if (typemap[x][y] == PORTAL) {
      if (done)
	return true;
      else
	return false;
    }
    if (typemap[x][y] != WALL) {
      return true;
    }
  }
  return false;
}

bool Map::blockedForEnemy(int x, int y) {
  if (0 <= x && x <= 79 && 0 <= y && y <= 24) {
    if (typemap[x][y] == TREASURE || typemap[x][y] == WALL || typemap[x][y] == PORTAL)
      return true;
    else
      return false;
  }
  return true;
}

int Map::getTreasure() {
  return numTreasure;
}
