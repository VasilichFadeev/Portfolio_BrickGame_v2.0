#include "desktop_snake.h"

namespace s21 {
void SnakeWindow::saveHighScore() {
  QFile file(HIGH_SCORE_FILE);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);
    out << highScore;
    file.close();
  }
}
}  // namespace s21