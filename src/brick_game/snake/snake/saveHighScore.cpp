#include "snake_terminal.h"

void SnakeGame::saveHighScore() {
  std::ofstream file(HIGH_SCORE_FILE);
  if (file.is_open()) {
    file << highScore;
    file.close();
  }
}