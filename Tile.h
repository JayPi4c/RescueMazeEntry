#include "Arduino.h"
#include "Vars.h"

#ifndef Tile_h
#define Tile_h
class Tile{
  public:
    Tile(void);  //Konstruktor
    ~Tile(void); //Destruktor
    void setWall(int dir, boolean state);
    boolean getWall(int dir);
    void setCheckpoint(boolean state);
    boolean getCheckpoint(void);
    void setBlack(boolean state);
    boolean getBlack(void);
    void setVisited(boolean state);
    boolean getVisited(void);
    
  private:  
    boolean WallNorth;
    boolean WallSouth;
    boolean WallEast;
    boolean WallWest;
    boolean Checkpoint;
    boolean black;
    boolean visited;
  };

  #endif
