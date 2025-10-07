#include "../../brick_game/snake/snake/snake_terminal.h"

void SnakeGame::spawnSnake() {
  srand(time(0));
  int y, x;
  do {
    y = rand() % 5 + 9;
    x = rand() % 4 + 4;
  } while (field[y][x] != L' ' || field[y + 1][x] != L' ' ||
           field[y + 2][x] != L' ' || field[y + 3][x] != L' ');

  snake.clear();

  snake.push_back({y + 3, x});
  field[y + 3][x] = L'█';

  snake.push_back({y + 2, x});
  field[y + 2][x] = L'█';

  snake.push_back({y + 1, x});
  field[y + 1][x] = L'█';

  snake.push_back({y, x});
  field[y][x] = L'█';

  directionX = 0;
  directionY = -1;
}