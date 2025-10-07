#include <random>

#include "../../../brick_game/snake/desktop_snake/desktop_snake.h"

namespace s21 {

void SnakeWindow::spawnSnake() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distY(9, 13);
  std::uniform_int_distribution<> distX(4, 7);

  int y, x;
  do {
    y = distY(gen);
    x = distX(gen);
  } while (field[y][x] != QChar(L' ') || field[y + 1][x] != QChar(L' ') ||
           field[y + 2][x] != QChar(L' ') || field[y + 3][x] != QChar(L' '));

  snake.clear();

  snake.push_back({y + 3, x});
  field[y + 3][x] = QChar(1);

  snake.push_back({y + 2, x});
  field[y + 2][x] = QChar(1);

  snake.push_back({y + 1, x});
  field[y + 1][x] = QChar(1);

  snake.push_back({y, x});
  field[y][x] = QChar(1);

  directionX = 0;
  directionY = -1;
}
}  // namespace s21