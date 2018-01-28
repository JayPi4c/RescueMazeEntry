#include "Tile.h"

Tile::Tile(void) {
  WallNorth = false;
  WallWest = false;
  WallSouth = false;
  WallEast = false;
  Checkpoint = false;
  black = false;
  visited = false;
}

Tile::~Tile(void) {

}

void Tile::setWall(int dir, boolean state) {
  switch (dir) {
    case NORTH:
      WallNorth = state;
      break;
    case WEST:
      WallWest = state;
      break;
    case SOUTH:
      WallSouth = state;
      break;
    case EAST:
      WallEast = state;
      break;
    default:
      break;
  }
}

boolean Tile::getWall(int dir) {
  switch (dir) {
    case NORTH:
      return WallNorth;
      break;
    case WEST:
      return WallWest;
      break;
    case SOUTH:
      return WallSouth;
      break;
    case EAST:
      return WallEast;
      break;
    default:
      return false;
      break;
  }
}

void Tile::setBlack(boolean state) {
  black = state;
}

boolean Tile::getBlack(void) {
  return black;
}

void Tile::setCheckpoint(boolean state) {
  Checkpoint = state;
}

boolean Tile::getCheckpoint(void) {
  return Checkpoint;
}

void Tile::setVisited(boolean state) {
  visited = state;
}

boolean Tile::getVisited(void) {
  return visited;
}


