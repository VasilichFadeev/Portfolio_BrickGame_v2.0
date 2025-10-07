#include "../../brick_game/tetris/brick_game.h"

void setupColors() {
  start_color();
  use_default_colors();
  init_pair(PINK_PAIR, PINK_COLOR, -1);
  init_pair(RED_PAIR, COLOR_RED, -1);
  init_pair(ORANGE_PAIR, ORANGE_COLOR, -1);
  init_pair(YELLOW_PAIR, COLOR_YELLOW, -1);
  init_pair(GREEN_PAIR, COLOR_GREEN, -1);
  init_pair(BLUE_PAIR, COLOR_BLUE, -1);
  init_pair(PURPLE_PAIR, PURPLE_COLOR, -1);
}