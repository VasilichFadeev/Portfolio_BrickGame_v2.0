/**
 * @file constructor.cpp
 * @brief Конструктор окна SnakeWindow.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Конструктор SnakeWindow.
 *
 * Инициализирует игру, загружает рекорд,
 * настраивает интерфейс и таймер, сбрасывает состояние игры.
 *
 * @param parent Родительский виджет
 */
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