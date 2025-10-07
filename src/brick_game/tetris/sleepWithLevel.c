#include "brick_game.h"

/**
 * @brief Пауза между тиком игры, зависящая от уровня.
 *
 * @param level Текущий уровень игры.
 */
void sleepWithLevel(int level) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = calculateSpeed(level) * 1000000L;
  nanosleep(&ts, NULL);
}