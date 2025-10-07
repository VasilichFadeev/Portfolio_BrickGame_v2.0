#include "desktop_snake.h"

namespace s21 {

void SnakeWindow::toggleTurbo() {
  if (!gameOver && !gameWon && !gamePaused) {
    isTurbo = !isTurbo;
    updateSpeed();
  }
}
}  // namespace s21