/**
 * @file resetGame.cpp
 * @brief Сброс состояния игры.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Сбрасывает игру: состояние, змею и яблоко.
 */
void SnakeWindow::resetGame() {
  gameOver = false;
  gameWon = false;
  fillFieldWithFrame();
  spawnSnake();
  generateApple();
  updateGameDisplay();
}
}  // namespace s21