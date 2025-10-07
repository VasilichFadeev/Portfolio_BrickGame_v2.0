#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Переключение состояния паузы.
 *
 * Если игра не окончена и не выиграна, меняет значение gamePaused.
 * При паузе останавливает таймер, при продолжении — обновляет скорость.
 * Обновляет отображение игрового поля.
 */
void SnakeWindow::togglePause() {
  if (!gameOver && !gameWon) {
    gamePaused = !gamePaused;
    if (gamePaused) {
      timer->stop();
    } else {
      updateSpeed();
    }
    updateGameDisplay();
  }
}
}  // namespace s21