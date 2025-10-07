#include "brick_game.h"

void mergeTetromino(const Tetromino *t, int field[HEIGHT][WIDTH]) {
  for (int y = 0; y < t->size; y++) {
    for (int x = 0; x < t->size; x++) {
      if (t->shape[y][x]) {
        field[t->y + y][t->x + x] = 1;
      }
    }
  }
}