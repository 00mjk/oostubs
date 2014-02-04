#ifndef __MAP_H__
#define __MAP_H__

/*
  Soll das Gelände repräsentieren.
  Kann zum Beispiel für Kollisionsabfragen gebraucht werden.
  Mögliche Levels können sich später von von Map ableiten,
  wobei Map::Map dann angepasst werden muss.

  Im Moment scheint kein Semaphor für die Map nötig zu sein,
  aber wir sollte das im Auge behalten.
 */
class Map {
 private:

  char typemap[80][25];
  int numTreasure;
  // wird gesetzt sobald alle Schätze gerafft sind
  bool done;

 public:
 
  Map();

  enum type { EMPTY, TREASURE, WALL, PORTAL, MONSTER, WALL_DESTRUCTIBLE };

  void print();
  char get(int x, int y);
  void set(int x, int y, char type);
  bool notBlocked(int x, int y);
  bool blockedForEnemy(int x, int y);
  int getTreasure();
  void setDone() { done = true; }
};

#endif
