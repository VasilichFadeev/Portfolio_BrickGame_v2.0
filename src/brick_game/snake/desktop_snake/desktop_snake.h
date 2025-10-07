#ifndef DESKTOP_SNAKE_H
#define DESKTOP_SNAKE_H

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <random>
#include <vector>

const int WIDTH = 12;
const int HEIGHT = 22;
const int FIELD_W = 10;
const int FIELD_H = 20;
const int MAX_LEVEL = 10;
const int WIN_LENGTH = 200;
const QString HIGH_SCORE_FILE = "snake_high_score.txt";

enum UserAction_t { Start, Pause, Terminate, Left, Right, Up, Down, Action };

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

struct SnakeSegment {
  int y;
  int x;
};

namespace s21 {
class SnakeWindow : public QWidget {
 public:
  explicit SnakeWindow(QWidget *parent = nullptr);
  void generateApple();
  QChar (*getField() const)[WIDTH] {
    return const_cast<QChar(*)[WIDTH]>(field);
  }
  void clearField();
  int getHighScore() { return highScore; }
  bool getGameWon() { return gameWon; }
  bool getGameOver() { return gameOver; }
  void loadHighScore();
  void saveHighScore();
  void resetGame();

 private:
  QTimer *timer;
  QLabel *gameLabel;
  QPushButton *startButton;
  QChar field[HEIGHT][WIDTH];
  std::vector<SnakeSegment> snake;
  int directionX;
  int directionY;
  bool gameOver;
  bool gamePaused;
  bool gameWon;
  bool isTurbo;
  int currentScore;
  int highScore;
  int currentLevel;

  void fillFieldWithFrame();
  void spawnSnake();
  void setupUI();
  void setupTimer();
  void startGame();
  void togglePause();
  void toggleTurbo();
  void updateSpeed();
  void updateGame();
  void keyPressEvent(QKeyEvent *event);
  void updateGameDisplay();
  GameInfo_t updateCurrentState();
};
}  // namespace s21

#endif