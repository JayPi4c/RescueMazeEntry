#include "Arduino.h"
#include "Vars.h"
#include "Tile.h"

#ifndef Map_h
#define Map_h
class Map {
  public:
    Map(int cols_, int rows_);
    ~Map(void);
    Tile getTile(int x, int y);
    void setCurrent(int x, int y);
    Tile getCurrent(void);

  private:
    int cols;
    int rows;
    Tile** maze;
    Tile current;
    int currentX;
    int currentY;
};

#endif
