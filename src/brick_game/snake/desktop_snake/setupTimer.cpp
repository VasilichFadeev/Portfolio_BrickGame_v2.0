#include "desktop_snake.h"

namespace s21 {

void SnakeWindow::setupTimer() {
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &SnakeWindow::updateGame);
}
}  // namespace s21