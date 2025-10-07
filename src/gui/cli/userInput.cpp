/**
 * @file userInput.cpp
 * @brief Реализация функции SnakeGame::userInput.
 */
#include "../../brick_game/snake/snake/snake_terminal.h"

namespace s21 {
/**
 * @brief Обрабатывает действия игрока.
 *
 * Поддерживает:
 * - Left, Right, Up, Down — изменение направления движения;
 * - Pause — пауза/возобновление игры;
 * - Turbo — включение/выключение ускорения;
 * - Terminate — завершение игры.
 *
 * @param action Действие игрока
 * @param hold Флаг удержания клавиши (игнорируется)
 */
void SnakeGame::userInput(UserAction_t action, bool hold) {
  if (hold || gameOver) return;

  switch (action) {
    case Left:
      if (directionX != 1) {
        directionX = -1;
        directionY = 0;
      }
      break;
    case Right:
      if (directionX != -1) {
        directionX = 1;
        directionY = 0;
      }
      break;
    case Up:
      if (directionY != 1) {
        directionX = 0;
        directionY = -1;
      }
      break;
    case Down:
      if (directionY != -1) {
        directionX = 0;
        directionY = 1;
      }
      break;
    case Pause:
      if (!gameOver && !gameWon) {
        gamePaused = !gamePaused;
      }
      break;
    case Turbo:
      if (!gameOver && !gameWon && !gamePaused) {
        isTurbo = !isTurbo;
      }
      break;
    case Terminate:
      gameOver = true;
      break;
    default:
      break;
  }
}
}