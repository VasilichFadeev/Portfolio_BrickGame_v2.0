/**
 * @file keyPressEvent.cpp
 * @brief Обработка клавиш для десктопной змейки.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Обрабатывает нажатия клавиш.
 *
 * - Стрелки: движение змеи
 * - SPACE: пауза
 * - E: турбо
 * - Q: закрытие окна
 *
 * @param event Событие нажатия клавиши
 */
void SnakeWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      if (directionX != 1) {
        directionX = -1;
        directionY = 0;
      }
      break;
    case Qt::Key_Right:
      if (directionX != -1) {
        directionX = 1;
        directionY = 0;
      }
      break;
    case Qt::Key_Up:
      if (directionY != 1) {
        directionX = 0;
        directionY = -1;
      }
      break;
    case Qt::Key_Down:
      if (directionY != -1) {
        directionX = 0;
        directionY = 1;
      }
      break;
    case Qt::Key_Space:
      togglePause();
      break;
    case Qt::Key_E:
      toggleTurbo();
      break;
    case Qt::Key_Q:
      this->close();
      break;
  }
}
}  // namespace s21