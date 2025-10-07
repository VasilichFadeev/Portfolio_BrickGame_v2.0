#include "desktop_snake.h"

namespace s21 {
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