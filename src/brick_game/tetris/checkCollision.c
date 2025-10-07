#include "brick_game.h"

int checkCollision(int nx, int ny, const int shape[4][4],
                   const int field[HEIGHT][WIDTH]) {
  int collision = 0;
  for (int y = 0; y < 4 && !collision; y++) {
    for (int x = 0; x < 4 && !collision; x++) {
      if (shape[y][x]) {
        int fx = nx + x;
        int fy = ny + y;
        collision =
            (fx <= 0 || fx >= WIDTH - 1 || fy >= HEIGHT - 1 || field[fy][fx]);
      }
    }
  }
  return collision;
}