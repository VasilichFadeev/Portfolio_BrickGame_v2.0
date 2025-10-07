/**
 * @file updateCurrentState.cpp
 * @brief Логика обновления состояния игры Snake.
 */
#include "snake_terminal.h"

namespace s21 {
/**
 * @brief Обновляет текущее состояние игры.
 *
 * Выполняет:
 * - обновление игровой информации в структуре `GameInfo_t`;
 * - проверку завершения игры (столкновение или победа);
 * - расчёт новой позиции головы змеи;
 * - проверку столкновений со стенами или телом змеи;
 * - обработку столкновений с яблоком;
 * - конвертацию поля в числовое представление.
 *
 * @return Текущая информация об игре (`GameInfo_t`).
 */
GameInfo_t SnakeGame::updateCurrentState() {
  GameInfo_t info = {};
  updateGameInfo(info);

  if (gameOver || gameWon || gamePaused) {
    return info;
  }

  SnakeSegment head = snake.back();
  int newY = head.y + directionY;
  int newX = head.x + directionX;

  // Проверка столкновений
  if (checkCollisionWithWalls(newY, newX) ||
      checkCollisionWithSelf(newY, newX)) {
    handleCollision(info);
    return info;
  }

  // Проверяем наличие яблока ДО движения змеи
  bool ateApple = (field[newY][newX] == L'●');

  // Двигаем змею
  moveSnake(newY, newX);

  // Обрабатываем столкновение с яблоком (если оно было)
  if (ateApple) {
    handleAppleCollision(info, newY, newX);
  }

  convertFieldToInt();
  return info;
}
}  // namespace s21