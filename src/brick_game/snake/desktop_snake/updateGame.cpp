#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Основной метод обновления игрового цикла.
 *
 * Проверяет состояние игры (gameOver, gameWon, gamePaused),
 * вызывает updateCurrentState() для движения змейки, обновляет счет и уровень.
 * Обновляет отображение игрового поля.
 */
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