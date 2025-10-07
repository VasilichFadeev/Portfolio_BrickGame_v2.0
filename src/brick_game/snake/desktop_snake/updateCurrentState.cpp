#include "desktop_snake.h"

namespace s21 {
GameInfo_t SnakeWindow::updateCurrentState() {
  GameInfo_t info = {};
  info.score = currentScore;
  info.level = currentLevel;

  SnakeSegment tail = snake.front();
  field[tail.y][tail.x] = QChar(L' ');
  snake.erase(snake.begin());

  SnakeSegment head = snake.back();
  int newY = head.y + directionY;
  int newX = head.x + directionX;

  if (field[newY][newX] == QChar(1) || field[newY][newX] == QChar(L'│') ||
      field[newY][newX] == QChar(L'─') || field[newY][newX] == QChar(L'┐') ||
      field[newY][newX] == QChar(L'┘') || field[newY][newX] == QChar(L'┌') ||
      field[newY][newX] == QChar(L'└')) {
    info.pause = 1;
    return info;
  }

  if (field[newY][newX] == QChar(2)) {
    info.score += 10;
    int newLevel = info.score / 50 + 1;
    if (newLevel > info.level && newLevel <= MAX_LEVEL) {
      info.level = newLevel;
      updateSpeed();
    }
    snake.insert(snake.begin(), tail);
    generateApple();
  }

  snake.push_back({newY, newX});
  field[newY][newX] = QChar(1);

  info.pause = 0;
  return info;
}
}  // namespace s21