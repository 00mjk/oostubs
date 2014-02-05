#include "map.h"

#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"
#include "library/random.h"

extern CGA_Stream kout;
extern Guarded_Semaphore sem_display;
extern Random r;

void Map::init(int numwalls) {
  numTreasure = 0;
  done = false;

  for (int i = 0; i < 80; i++)
    for (int j = 0; j < 25; j++)
      typemap[i][j] = EMPTY;

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
  for (int i = 0; i != 10; ++i) {
    int x = r.number() % 78 + 1;
    int y = r.number() % 23 + 1;

    if (get(x, y) == EMPTY)
      set(x, y, TREASURE);
  }
  typemap[20][8] = WALL;
  typemap[20][9] = WALL;
  typemap[20][10] = WALL;
  typemap[20][11] = WALL;
  typemap[20][12] = WALL;
  typemap[20][13] = WALL;
  typemap[20][14] = WALL;
  typemap[20][15] = WALL;
  typemap[20][16] = WALL;

  
  typemap[60][8] = WALL;
  typemap[60][9] = WALL;
  typemap[60][10] = WALL;
  typemap[60][11] = WALL;
  typemap[60][12] = WALL;
  typemap[60][13] = WALL;
  typemap[60][14] = WALL;
  typemap[60][15] = WALL;
  typemap[60][16] = WALL;

  for (int i = 0; i != numwalls; ++i) {
    int x = r.number() % 78 + 1;
    int y = r.number() % 23 + 1;

    if (get(x, y) == EMPTY)
      set(x, y, WALL_DESTRUCTIBLE);
  }
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
	kout.show(x,y, 79, 0x09);
	break;
      case WALL_DESTRUCTIBLE:
	kout.show(x,y, 176, 0x06);
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
    if (typemap[x][y] != WALL && typemap[x][y] != WALL_DESTRUCTIBLE) {
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
