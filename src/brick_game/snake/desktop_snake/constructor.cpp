#include "desktop_snake.h"

namespace s21 {

SnakeWindow::SnakeWindow(QWidget *parent)
    : QWidget(parent),
      gameOver(false),
      gamePaused(false),
      gameWon(false),
      isTurbo(false),
      currentScore(0),
      highScore(0),
      currentLevel(1) {
  loadHighScore();
  setupUI();
  setupTimer();
  resetGame();
}
}  // namespace s21