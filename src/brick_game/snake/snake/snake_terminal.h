#ifndef SNAKE_TERMINAL_H
#define SNAKE_TERMINAL_H

#include <locale.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

const int WIDTH = 12;
const int HEIGHT = 22;
const int FIELD_W = 10;
const int FIELD_H = 20;
const int MAX_LEVEL = 10;
const int WIN_LENGTH = 200;
const std::string HIGH_SCORE_FILE = "snake_high_score.txt";

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Turbo
} UserAction_t;

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

class SnakeGame {
 private:
  int directionX;
  int directionY;
  bool gameOver;
  bool gamePaused;
  bool isTurbo;
  void fillFieldWithFrame();
  void spawnSnake();
  void generateApple();
  void convertFieldToInt();

 public:
  std::vector<SnakeSegment> snake;
  bool gameWon;
  int currentScore;
  int currentLevel;
  int highScore;
  wchar_t field[HEIGHT][WIDTH];
  int **fieldInt;
  int **nextInt;

  SnakeGame();
  ~SnakeGame();

  int getHighScore() { return highScore; }
  void setCurrentLevel(int level) { currentLevel = level; }
  void setTurbo(bool turbo) { isTurbo = turbo; }
  void setPaused(bool paused) { gamePaused = paused; }
  int getCurrentLevel() const { return currentLevel; }
  void loadHighScore();
  void saveHighScore();

  void userInput(UserAction_t action, bool hold);
  void updateGameInfo(GameInfo_t &info);
  bool checkCollisionWithWalls(int newY, int newX);
  bool checkCollisionWithSelf(int newY, int newX);
  void handleCollision(GameInfo_t &info);
  void moveSnake(int newY, int newX);
  void handleAppleCollision(GameInfo_t &info, int newY, int newX);
  void checkWinCondition(GameInfo_t &info);
  GameInfo_t updateCurrentState();
  bool getTurboState() const;
  bool isGameOver() const;
};

extern SnakeGame *game;

extern "C" {
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void initializeGame();
void terminateGame();
}

void inputHandler(bool &paused, bool &running);
void turbo();
void drawField(bool &paused, GameInfo_t &info);
void run(bool &running, int &ch, bool &paused);

#endif