#include "desktop_snake.h"

namespace s21 {
void SnakeWindow::updateGame() {
  if (gameOver || gameWon) {
    timer->stop();
    updateGameDisplay();
    if (currentScore > highScore) {
      highScore = currentScore;
      saveHighScore();
    }
    return;
  }
  if (!gamePaused) {
    GameInfo_t info = updateCurrentState();
    gameOver = (info.pause == 1);
    if (snake.size() >= WIN_LENGTH) gameWon = true;
    currentScore = info.score;
    currentLevel = info.level;
    updateGameDisplay();
  } else {
    updateGameDisplay();
  }
}
}  // namespace s21