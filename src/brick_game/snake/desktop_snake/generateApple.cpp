#include <random>

#include "desktop_snake.h"

namespace s21 {

void SnakeWindow::generateApple() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distY(1, HEIGHT - 2);
  std::uniform_int_distribution<> distX(1, WIDTH - 2);

  int y, x;
  do {
    y = distY(gen);
    x = distX(gen);
  } while (field[y][x] != QChar(L' '));

  field[y][x] = QChar(2);
}
}  // namespace s21