#include "Map.h"

Map::Map(int cols_, int rows_) {
  cols = cols_;
  rows = rows_;

  maze = new Tile*[rows];
  for (int i = 0; i < rows; i++) {
    maze[i] = new Tile[cols];
  }
}
Map::~Map(void) {

}
Tile Map::getTile(int x, int y) {
  return maze[x][y];
}
void Map::setCurrent(int x, int y) {
  currentX = x;
  currentY = y;
  current = maze[currentX][currentY];
}
Tile Map::getCurrent(void) {
  return current;
}

