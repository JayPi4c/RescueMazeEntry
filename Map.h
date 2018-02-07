#include "Arduino.h"
#include "Vars.h"
#include "Tile.h"

#ifndef Map_h
#define Map_h


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
