#include "brick_game.h"

void writeHighScore(int score) {
  FILE *file = fopen(HIGH_SCORE_FILE, "w");
  if (file == NULL) {
    return;
  }
  fprintf(file, "%d", score);
  fclose(file);
}