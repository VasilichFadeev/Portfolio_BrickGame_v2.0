#include "brick_game.h"

void rotate(int shape[4][4], int result[4][4]) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) result[x][3 - y] = shape[y][x];
}