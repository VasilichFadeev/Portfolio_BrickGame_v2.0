/**
 * @file startGame.cpp
 * @brief Запуск игры.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Инициализирует стартовое состояние игры.
 *
 * Сбрасывает очки, уровень, паузу и турбо, обновляет интерфейс.
 */
void SnakeWindow::startGame() {
  currentScore = 0;
  currentLevel = 1;
  isTurbo = false;
  gamePaused = false;
  gameOver = false;
  gameWon = false;

  updateGameDisplay();
  startButton->hide();
  gameLabel->show();

  resetGame();
  updateSpeed();
  setFocus();
}
}  // namespace s21