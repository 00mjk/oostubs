#ifndef __MAP_H__
#define __MAP_H__

/*
  Soll das Gelände repräsentieren.
  Kann zum Beispiel für Kollisionsabfragen gebraucht werden.
  Mögliche Levels können sich später von von Map ableiten,
  wobei Map::Map dann angepasst werden muss.
 */
class Map {
 private:

  enum type { EMPTY, TREASURE, WALL };

  char typemap[80][25];

 public:
 
  Map();

  void print();
  char get(int x, int y);
  bool notBlocked(int x, int y);
};

#endif
