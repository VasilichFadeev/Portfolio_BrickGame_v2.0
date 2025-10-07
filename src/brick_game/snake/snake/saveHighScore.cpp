#include "snake_terminal.h"

namespace s21 {
/**
 * @brief Сохраняет текущий рекорд в файл.
 *
 * Записывает значение `highScore` в файл `HIGH_SCORE_FILE`.
 */
void SnakeGame::saveHighScore() {
  std::ofstream file(HIGH_SCORE_FILE);
  if (file.is_open()) {
    file << highScore;
    file.close();
  }
}
}  // namespace s21