#include "brick_game.h"

void spawnTetromino(Tetromino *current, Tetromino *next) {
  *current = *next;
  current->x = WIDTH / 2 - 2;
  current->y = 1;

  initNextTetromino(next);
}