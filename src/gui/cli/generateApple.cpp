#include "../../brick_game/snake/snake/snake_terminal.h"

void SnakeGame::generateApple() {
  srand(time(0));
  int y, x;
  do {
    y = rand() % (HEIGHT - 2) + 1;
    x = rand() % (WIDTH - 2) + 1;
  } while (field[y][x] != L' ');
  field[y][x] = L'●';
}