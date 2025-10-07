#include "brick_game.h"

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