#include "Arduino.h"
#include "Vars.h"
#include "Tile.h"

#ifndef Map_h
#define Map_h

// Diese Klasse soll das speichern einer Karte und somit das erreichen von Floating Walls
// erleichtern!
class Map{
  public:
  Map(int cols_, int rows_);
  ~Map(void);
  int getCurrentX(void);
  int getCurrnetY(void);
  void setCurrentX(int x);
  void setCurrentY(int y);
  Tile getCurrent(void);
  
  private:
    Tile** maze;
    int currentX;
    int currentY;
    int cols;
    int rows;
  };

#endif
