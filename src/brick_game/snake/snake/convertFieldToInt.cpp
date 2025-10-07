#include "snake_terminal.h"

void SnakeGame::convertFieldToInt() {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (field[y][x] == L'█') {
        fieldInt[y][x] = 1;
      } else if (field[y][x] == L'●') {
        fieldInt[y][x] = 2;
      } else {
        fieldInt[y][x] = 0;
      }
    }
  }
}