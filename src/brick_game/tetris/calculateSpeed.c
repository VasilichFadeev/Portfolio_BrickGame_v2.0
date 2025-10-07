#include "brick_game.h"

/**
 * @brief Рассчитывает скорость падения фигур в зависимости от уровня.
 *
 * @param level Текущий уровень игры (0–10).
 * @return Значение скорости (1–10 для уровней 0–9, 10 для 10+).
 */
int calculateSpeed(int level) {
  int speed;
  if ((level >= 0) && (level <= 9)) {
    speed = level + 1;
  } else if (level >= 10) {
    speed = 10;
  } else {
    speed = 0;
  }
  return speed;
}