#include "../../brick_game/snake/snake/snake_terminal.h"

void SnakeGame::fillFieldWithFrame() {
  for (int x = 0; x < WIDTH; ++x) {
    if (x == 0) {
      field[0][x] = L'┌';
      field[HEIGHT - 1][x] = L'└';
    } else if (x == WIDTH - 1) {
      field[0][x] = L'┐';
      field[HEIGHT - 1][x] = L'┘';
    } else {
      field[0][x] = field[HEIGHT - 1][x] = L'─';
    }
  }

  for (int y = 1; y < HEIGHT - 1; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (x == 0 || x == WIDTH - 1) {
        field[y][x] = L'│';
      } else {
        field[y][x] = L' ';
      }
    }
  }
}