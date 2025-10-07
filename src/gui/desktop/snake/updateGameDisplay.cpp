#include "../../../brick_game/snake/desktop_snake/desktop_snake.h"

namespace s21 {
void SnakeWindow::updateGameDisplay() {
  QString html = "<pre style='font-family:Monospace; font-size:12px;'>";
  html += QString("Score: %1  Level: %2  High: %3")
              .arg(currentScore)
              .arg(currentLevel)
              .arg(highScore);

  if (isTurbo) {
    html += " <span style='color:orange;'>(TURBO)</span>";
  }
  html += "<br>";

  int centerY = HEIGHT / 2;
  int centerX = (WIDTH - 6) / 2;

  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (gameOver && y == centerY && x == centerX) {
        html += "<span style='color:blue; font-weight:bold;'>GAME OVER</span>";
        x += 8;
        continue;
      }
      if (gameWon && y == centerY && x == centerX) {
        html += "<span style='color:gold; font-weight:bold;'>YOU WIN!</span>";
        x += 7;
        continue;
      }
      if (gamePaused && !gameOver && !gameWon && y == centerY && x == centerX) {
        html += "<span style='color:blue; font-weight:bold;'>PAUSED</span>";
        x += 5;
        continue;
      }
      if (field[y][x] == QChar(2)) {
        html += "<span style='color:red;'>●</span>";
      } else if (field[y][x] == QChar(1)) {
        html += "<span style='color:green;'>█</span>";
      } else {
        html += field[y][x];
      }
    }
    html += "<br>";
  }

  html += "</pre>";
  gameLabel->setText(html);
}
}  // namespace s21