/**
 * @file saveHighScore.cpp
 * @brief Сохранение рекорда в файл.
 */
#include "desktop_snake.h"

namespace s21 {
/**
 * @brief Сохраняет текущий рекорд в HIGH_SCORE_FILE.
 */
void SnakeWindow::saveHighScore() {
  QFile file(HIGH_SCORE_FILE);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    out << highScore;
    file.close();
  }
}
}  // namespace s21