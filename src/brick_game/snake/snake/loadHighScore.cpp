#include "snake_terminal.h"

namespace s21 {
/**
 * @brief Загружает рекорд из файла.
 *
 * Читает значение из файла `HIGH_SCORE_FILE` и сохраняет его в `highScore`.
 * Если файл отсутствует, значение рекорда остаётся равным 0.
 */
void SnakeGame::loadHighScore() {
  std::ifstream file(HIGH_SCORE_FILE);
  if (file.is_open()) {
    file >> highScore;
    file.close();
  }
}
}  // namespace s21