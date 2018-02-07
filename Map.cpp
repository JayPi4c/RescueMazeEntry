#include "Map.h"

Map::Map(int cols_, int rows_) {
  cols = cols_;
  rows = rows_;
  maze = new Tile*[rows];
  for (int i = 0; i < rows; i++) {
    maze[i] = new Tile[cols];
  }
}

Map::~Map(void) {}

int Map::getCurrentX(void) {
  return currentX;
}
int Map::getCurrnetY(void) {
  return currentY;
}
void Map::setCurrentX(int x) {
  currentX = x;
}
void Map::setCurrentY(int y) {
  currentY = y;
}
Tile Map::getCurrent(void) {
  return maze[currentX][currentY];
}
