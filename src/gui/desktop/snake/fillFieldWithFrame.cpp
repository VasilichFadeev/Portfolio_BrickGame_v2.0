#include "../../../brick_game/snake/desktop_snake/desktop_snake.h"

namespace s21 {
void SnakeWindow::fillFieldWithFrame() {
  for (int x = 0; x < WIDTH; ++x) {
    if (x == 0) {
      field[0][x] = QChar(L'┌');
      field[HEIGHT - 1][x] = QChar(L'└');
    } else if (x == WIDTH - 1) {
      field[0][x] = QChar(L'┐');
      field[HEIGHT - 1][x] = QChar(L'┘');
    } else {
      field[0][x] = field[HEIGHT - 1][x] = QChar(L'─');
    }
  }

  for (int y = 1; y < HEIGHT - 1; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (x == 0 || x == WIDTH - 1) {
        field[y][x] = QChar(L'│');
      } else {
        field[y][x] = QChar(L' ');
      }
    }
  }
}
}  // namespace s21