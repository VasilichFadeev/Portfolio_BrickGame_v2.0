#include "brick_game.h"

void sleepWithLevel(int level) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = calculateSpeed(level) * 1000000L;
  nanosleep(&ts, NULL);
}