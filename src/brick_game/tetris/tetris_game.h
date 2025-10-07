#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <QChar>
#include <QString>
#include <random>
#include <vector>

const int FIELD_W = 10;
const int FIELD_H = 20;
const int WIDTH = FIELD_W + 2;
const int HEIGHT = FIELD_H + 2;

enum UserAction_t { Start, Pause, Terminate, Left, Right, Up, Down, Action };
enum PieceColor { PINK = 0, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };

struct Piece {
  int shape[4][4];
  PieceColor color;
};

class TetrisGame {
 public:
  TetrisGame();
  void reset();
  void userInput(UserAction_t action);
  bool update();
  QString render() const;
  int getSpeed() const;
  bool isPaused() const;
  int getHighScore() const { return highScore; }
  void loadHighScore();
  void saveHighScore();
  void spawnPiece();
  bool isValid(const int shape[4][4], int x, int y) const;
  void placePiece();
  void checkLines();

  int getCurrentX() const { return currentX; }
  int getCurrentY() const { return currentY; }
  int getScore() const { return score; }
  int getLevel() const { return level; }
  const Piece& getCurrentPiece() const { return currentPiece; }
  const Piece& getNextPiece() const { return nextPiece; }
  int getWidth() { return WIDTH; }
  int getHeight() { return HEIGHT; }

  std::vector<std::vector<QChar>> field;
  std::vector<std::vector<QString>> colors;
  int score = 0;

 private:
  std::vector<Piece> pieces;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> dist;

  int highScore = 0;
  int level = 1;
  int speed = 400;
  bool pause = false;

  Piece currentPiece;
  Piece nextPiece;
  int currentX = 4;
  int currentY = 1;
};

QString getColorCode(PieceColor color);

#endif  // TETRIS_GAME_H