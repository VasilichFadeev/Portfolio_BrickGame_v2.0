#include "desktop_snake.h"

namespace s21 {
void SnakeWindow::updateSpeed() {
  int speed = 300 - (currentLevel * 25);
  if (speed < 50) speed = 50;
  if (isTurbo) speed /= 2;
  timer->start(speed);
}
}  // namespace s21