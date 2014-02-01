#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

/*
Zählt die Anzahl eingesammelter Schätze, wie oft der Spieler von Monstern
getroffen wurde und welcher noch zu implementierende Kram sonst noch so
aufgesammelt wurde. Gibt diese Informationen schmucklos aus.

Könnte auch als senkrechter Bereich an der Rechten Seite implementiert werden.

Im Moment nicht extra geschützt. Falls Codeabschnitte, die den Status
verändern allerdings schon den sem_player verwenden, wird es nicht zu
Problemen kommen.
 */
class Statusbar {
 private:
  int treasure;
  int hits;
 public:
  Statusbar();
  void print();
  void inc_treasure();
  void inc_hits();
};


#endif
