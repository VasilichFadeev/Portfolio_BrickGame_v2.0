#include "snake_terminal.h"

void SnakeGame::loadHighScore() {
  std::ifstream file(HIGH_SCORE_FILE);
  if (file.is_open()) {
    file >> highScore;
    file.close();
  }
}