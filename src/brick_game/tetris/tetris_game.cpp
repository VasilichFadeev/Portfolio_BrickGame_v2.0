#include "tetris_game.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

TetrisGame::TetrisGame() {
  pieces = {{{{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, PINK},
            {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, RED},
            {{{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, ORANGE},
            {{{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}, YELLOW},
            {{{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, GREEN},
            {{{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, BLUE},
            {{{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, PURPLE}};
  gen = std::mt19937(rd());
  dist = std::uniform_int_distribution<>(0, 6);
  reset();
}

void TetrisGame::reset() {
  field.resize(HEIGHT, std::vector<QChar>(WIDTH, ' '));
  colors.resize(HEIGHT, std::vector<QString>(WIDTH, "#FFFFFF"));
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (y == 0 && x == 0)
        field[y][x] = QChar(L'┌');
      else if (y == 0 && x == WIDTH - 1)
        field[y][x] = QChar(L'┐');
      else if (y == HEIGHT - 1 && x == 0)
        field[y][x] = QChar(L'└');
      else if (y == HEIGHT - 1 && x == WIDTH - 1)
        field[y][x] = QChar(L'┘');
      else if (y == 0 || y == HEIGHT - 1)
        field[y][x] = QChar(L'─');
      else if (x == 0 || x == WIDTH - 1)
        field[y][x] = QChar(L'│');
      else
        field[y][x] = QChar(' ');
    }
  }
  score = 0;
  level = 1;
  pause = false;
  speed = 400;
  currentX = 4;
  currentY = 1;
  loadHighScore();
  nextPiece = pieces[dist(gen)];
  spawnPiece();
}

void TetrisGame::loadHighScore() {
  QFile file("./tetris_high_score.txt");
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in >> highScore;
    file.close();
  }
}

void TetrisGame::saveHighScore() {
  if (score > highScore) {
    highScore = score;
    QFile file("./tetris_high_score.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << highScore;
      file.close();
    }
  }
}

bool TetrisGame::update() {
  if (pause) return false;
  if (!isValid(currentPiece.shape, currentX, currentY + 1)) {
    placePiece();
    checkLines();
    spawnPiece();
    if (!isValid(currentPiece.shape, currentX, currentY)) {
      pause = true;
      saveHighScore();
      return false;
    }
  } else {
    currentY++;
  }
  return true;
}

int TetrisGame::getSpeed() const { return speed; }
bool TetrisGame::isPaused() const { return pause; }

void TetrisGame::spawnPiece() {
  currentPiece = nextPiece;
  nextPiece = pieces[dist(gen)];
  currentX = 4;
  currentY = 1;
  level = std::min(10, score / 600 + 1);
  speed = std::max(100, 400 - (level - 1) * 30);
}

bool TetrisGame::isValid(const int shape[4][4], int x, int y) const {
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (shape[i][j]) {
        int newX = x + j;
        int newY = y + i;
        if (newX <= 0 || newX >= WIDTH - 1 || newY >= HEIGHT - 1) return false;
        if (newY > 0 && field[newY][newX] == QChar(L'█')) return false;
      }
  return true;
}

void TetrisGame::checkLines() {
  int lines = 0;
  for (int y = HEIGHT - 2; y > 0; --y) {
    bool full = true;
    for (int x = 1; x < WIDTH - 1; ++x)
      if (field[y][x] != QChar(L'█')) {
        full = false;
        break;
      }
    if (full) {
      ++lines;
      for (int row = y; row > 1; --row)
        for (int x = 1; x < WIDTH - 1; ++x) {
          field[row][x] = field[row - 1][x];
          colors[row][x] = colors[row - 1][x];
        }
      for (int x = 1; x < WIDTH - 1; ++x) {
        field[1][x] = QChar(' ');
        colors[1][x] = "#FFFFFF";
      }
      y++;
    }
  }

  switch (lines) {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 700;
      break;
    case 4:
      score += 1500;
      break;
  }
}