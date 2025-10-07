#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Обновляет скорость таймера в зависимости от уровня и турбо-режима.
 *
 * - Базовая скорость: 300 - (level * 25)
 * - Минимальная скорость: 50 мс
 * - Если включен турбо-режим, скорость делится на 2
 */
void SnakeWindow::updateSpeed() {
  int speed = 300 - (currentLevel * 25);
  if (speed < 50) speed = 50;
  if (isTurbo) speed /= 2;
  timer->start(speed);
}
}  // namespace s21