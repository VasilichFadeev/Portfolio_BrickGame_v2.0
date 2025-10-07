#include "brick_game.h"

int readHighScore() {
  FILE *file = fopen(HIGH_SCORE_FILE, "r");
  int highScore = 0;
  if (file != NULL) {
    fscanf(file, "%d", &highScore);
    fclose(file);
  }
  return highScore;
}