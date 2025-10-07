#include "brick_game.h"

/**
 * @brief Читает рекорд из файла.
 *
 * @return Текущее значение рекорда или 0, если файл отсутствует.
 */
int readHighScore() {
  FILE *file = fopen(HIGH_SCORE_FILE, "r");
  int highScore = 0;
  if (file != NULL) {
    fscanf(file, "%d", &highScore);
    fclose(file);
  }
  return highScore;
}