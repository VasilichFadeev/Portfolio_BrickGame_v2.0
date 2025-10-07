#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Обновляет текущее состояние игры.
 *
 * Перемещает голову змейки, проверяет столкновения с границами и телом.
 * Если встречено яблоко, увеличивает счет и, при необходимости, уровень,
 * генерирует новое яблоко и восстанавливает хвост змейки.
 *
 * @return GameInfo_t структура с обновленными значениями:
 *   - score: текущий счет
 *   - level: текущий уровень
 *   - pause: флаг, указывающий на необходимость остановки игры (1 —
 * столкновение)
 */
GameInfo_t SnakeWindow::updateCurrentState() {
  GameInfo_t info = {};
  info.score = currentScore;
  info.level = currentLevel;

  SnakeSegment tail = snake.front();
  field[tail.y][tail.x] = QChar(L' ');
  snake.erase(snake.begin());

  SnakeSegment head = snake.back();
  int newY = head.y + directionY;
  int newX = head.x + directionX;

  if (field[newY][newX] == QChar(1) || field[newY][newX] == QChar(L'│') ||
      field[newY][newX] == QChar(L'─') || field[newY][newX] == QChar(L'┐') ||
      field[newY][newX] == QChar(L'┘') || field[newY][newX] == QChar(L'┌') ||
      field[newY][newX] == QChar(L'└')) {
    info.pause = 1;
    return info;
  }

  if (field[newY][newX] == QChar(2)) {
    info.score += 10;
    int newLevel = info.score / 50 + 1;
    if (newLevel > info.level && newLevel <= MAX_LEVEL) {
      info.level = newLevel;
      updateSpeed();
    }
    snake.insert(snake.begin(), tail);
    generateApple();
  }

  snake.push_back({newY, newX});
  field[newY][newX] = QChar(1);

  info.pause = 0;
  return info;
}
}  // namespace s21