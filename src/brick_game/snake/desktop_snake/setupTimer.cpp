/**
 * @file setupTimer.cpp
 * @brief Настройка таймера игры.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Настраивает QTimer для обновления игры.
 */
void SnakeWindow::setupTimer() {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &SnakeWindow::updateGame);
}
}  // namespace s21