#include "desktop_snake.h"

namespace s21 {
void SnakeWindow::loadHighScore() {
  QFile file(HIGH_SCORE_FILE);
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    in >> highScore;
    if (in.status() != QTextStream::Ok || highScore < 0) {
      highScore = 0;
    }
    file.close();
  } else {
    highScore = 0;
  }
}
}  // namespace s21