#include "desktop_snake.h"

namespace s21 {

void SnakeWindow::resetGame() {
  gameOver = false;
  gameWon = false;
  fillFieldWithFrame();
  spawnSnake();
  generateApple();
  updateGameDisplay();
}
}  // namespace s21