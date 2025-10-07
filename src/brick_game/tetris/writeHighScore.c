#include "brick_game.h"

/**
 * @brief Записывает рекорд в файл.
 *
 * @param score Значение рекорда для записи.
 */
void writeHighScore(int score) {
  FILE *file = fopen(HIGH_SCORE_FILE, "w");
  if (file == NULL) {
    return;
  }
  fprintf(file, "%d", score);
  fclose(file);
}