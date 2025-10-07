#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Переключение турбо-режима.
 *
 * Если игра не окончена, не выиграна и не на паузе, меняет значение isTurbo.
 * После переключения обновляет скорость игры.
 */
void SnakeWindow::toggleTurbo() {
  if (!gameOver && !gameWon && !gamePaused) {
    isTurbo = !isTurbo;
    updateSpeed();
  }
}
}  // namespace s21