#include "brick_game.h"

int handleTick(int *tick, Tetromino *current, Tetromino *next,
               int field[HEIGHT][WIDTH], int *points, int *level,
               int *highScore) {
  if (++(*tick) >= 10 - *level) {
    *tick = 0;
    if (!checkCollision(current->x, current->y + 1, current->shape, field)) {
      current->y++;
    } else {
      mergeTetromino(current, field);
      clearLines(points, level, field);
      if (*points > *highScore) {
        *highScore = *points;
        writeHighScore(*highScore);
      }
      spawnTetromino(current, next);
      if (checkCollision(current->x, current->y, current->shape, field)) {
        return 1;
      }
    }
  }
  return 0;
}