#include "../../../brick_game/tetris/tetris_game.h"

QString TetrisGame::render() const {
  QChar temp[HEIGHT][WIDTH];
  QString tempColors[HEIGHT][WIDTH];
  for (int y = 0; y < HEIGHT; ++y)
    for (int x = 0; x < WIDTH; ++x) {
      temp[y][x] = field[y][x];
      tempColors[y][x] = colors[y][x];
    }

  QString pieceColor = getColorCode(currentPiece.color);
  if (!pause) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        if (currentPiece.shape[i][j]) {
          int x = currentX + j;
          int y = currentY + i;
          if (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1) {
            temp[y][x] = QChar(L'█');
            tempColors[y][x] = pieceColor;
          }
        }
  }

  QString result;
  result += "<html><body><table><tr>";

  // Левая колонка: игровое поле + статистика
  result +=
      "<td><pre style='font-family: monospace; background-color: white; "
      "color: black;'>";

  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      QString fg = temp[y][x] == QChar(L'█') ? tempColors[y][x] : "#000000";
      QString bg = "#FFFFFF";
      result +=
          QString("<span style='color:%1; background-color:%2;'>%3</span>")
              .arg(fg)
              .arg(bg)
              .arg(temp[y][x]);
    }

    // Статистика рядом с полем
    if (y == 2)
      result +=
          QString("   <span style='color:black;'>Score: %1</span>").arg(score);
    else if (y == 3)
      result +=
          QString("   <span style='color:black;'>Level: %1</span>").arg(level);
    else if (y == 4)
      result += QString("   <span style='color:black;'>High: %1</span>")
                    .arg(highScore);
    else if (y == 5 && pause)
      result += QString("   <span style='color:red;'>%1</span>")
                    .arg(isValid(currentPiece.shape, currentX, currentY)
                             ? "PAUSED (Space)"
                             : "GAME OVER");

    result += "\n";
  }

  result += "</pre></td>";

  // Правая колонка: следующая фигура
  result +=
      "<td><pre style='font-family: monospace; background-color: white; "
      "color: black;'>";
  result += "<span style='color:black;'>Next:</span>\n";
  for (int i = 0; i < 4; ++i) {
    result += "    ";
    for (int j = 0; j < 4; ++j) {
      QChar ch = nextPiece.shape[i][j] ? QChar(L'█') : QChar(' ');
      QString fg =
          nextPiece.shape[i][j] ? getColorCode(nextPiece.color) : "#FFFFFF";
      result += QString("<span style='color:%1;'>%2</span>").arg(fg).arg(ch);
    }
    result += "\n";
  }
  result += "</pre></td>";

  result += "</tr></table></body></html>";
  return result;
}