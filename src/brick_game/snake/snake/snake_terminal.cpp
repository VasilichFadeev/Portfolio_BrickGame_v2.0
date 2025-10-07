#include "snake_terminal.h"

SnakeGame* game = nullptr;

SnakeGame::SnakeGame() {
  fieldInt = new int*[HEIGHT];
  nextInt = new int*[HEIGHT];
  for (int i = 0; i < HEIGHT; ++i) {
    fieldInt[i] = new int[WIDTH];
    nextInt[i] = new int[WIDTH];
  }

  directionX = 1;
  directionY = 0;
  gameOver = false;
  gamePaused = false;
  gameWon = false;
  isTurbo = false;
  currentScore = 0;
  highScore = 0;
  currentLevel = 1;

  loadHighScore();
  fillFieldWithFrame();
  spawnSnake();
  generateApple();
  convertFieldToInt();
}

SnakeGame::~SnakeGame() {
  for (int i = 0; i < HEIGHT; ++i) {
    delete[] fieldInt[i];
    delete[] nextInt[i];
  }
  delete[] fieldInt;
  delete[] nextInt;
}

void SnakeGame::userInput(UserAction_t action, bool hold) {
  if (hold || gameOver) return;

  switch (action) {
    case Left:
      if (directionX != 1) {
        directionX = -1;
        directionY = 0;
      }
      break;
    case Right:
      if (directionX != -1) {
        directionX = 1;
        directionY = 0;
      }
      break;
    case Up:
      if (directionY != 1) {
        directionX = 0;
        directionY = -1;
      }
      break;
    case Down:
      if (directionY != -1) {
        directionX = 0;
        directionY = 1;
      }
      break;
    case Pause:
      if (!gameOver && !gameWon) {
        gamePaused = !gamePaused;
      }
      break;
    case Turbo:
      if (!gameOver && !gameWon && !gamePaused) {
        isTurbo = !isTurbo;
      }
      break;
    case Terminate:
      gameOver = true;
      break;
    default:
      break;
  }
}

void SnakeGame::updateGameInfo(GameInfo_t& info) {
  info.field = fieldInt;
  info.next = nextInt;
  info.score = currentScore;
  info.high_score = highScore;
  info.level = currentLevel;
  info.speed = 300 - (currentLevel * 25);
  if (info.speed < 50) info.speed = 50;

  if (isTurbo) {
    info.speed /= 2;
  }

  info.pause = gamePaused ? 1 : 0;
}

bool SnakeGame::checkCollisionWithWalls(int newY, int newX) {
  return (newX <= 0 || newX >= WIDTH - 1 || newY <= 0 || newY >= HEIGHT - 1);
}

bool SnakeGame::checkCollisionWithSelf(int newY, int newX) {
  for (size_t i = 0; i < snake.size() - 1; ++i) {
    if (snake[i].x == newX && snake[i].y == newY) {
      return true;
    }
  }
  return false;
}

void SnakeGame::handleCollision(GameInfo_t& info) {
  gameOver = true;
  if (currentScore > highScore) {
    highScore = currentScore;
    saveHighScore();
  }
  info.pause = 1;
}

void SnakeGame::moveSnake(int newY, int newX) {
  SnakeSegment tail = snake.front();
  field[tail.y][tail.x] = L' ';
  snake.erase(snake.begin());
  snake.push_back({newY, newX});
  field[newY][newX] = L'█';
}

void SnakeGame::handleAppleCollision(GameInfo_t& info, int newY, int newX) {
  currentScore += 10;
  int newLevel = currentScore / 50 + 1;
  if (newLevel > currentLevel && newLevel <= MAX_LEVEL) {
    currentLevel = newLevel;
  }

  SnakeSegment tail = snake.front();
  snake.insert(snake.begin(), tail);

  generateApple();
  checkWinCondition(info);
}

void SnakeGame::checkWinCondition(GameInfo_t& info) {
  if (snake.size() >= WIN_LENGTH) {
    gameWon = true;
    if (currentScore > highScore) {
      highScore = currentScore;
      saveHighScore();
    }
    info.pause = 1;
  }
}

GameInfo_t SnakeGame::updateCurrentState() {
  GameInfo_t info = {};
  updateGameInfo(info);

  if (gameOver || gameWon || gamePaused) {
    return info;
  }

  SnakeSegment head = snake.back();
  int newY = head.y + directionY;
  int newX = head.x + directionX;

  // Проверка столкновений
  if (checkCollisionWithWalls(newY, newX) ||
      checkCollisionWithSelf(newY, newX)) {
    handleCollision(info);
    return info;
  }

  // Проверяем наличие яблока ДО движения змеи
  bool ateApple = (field[newY][newX] == L'●');

  // Двигаем змею
  moveSnake(newY, newX);

  // Обрабатываем столкновение с яблоком (если оно было)
  if (ateApple) {
    handleAppleCollision(info, newY, newX);
  }

  convertFieldToInt();
  return info;
}

bool SnakeGame::getTurboState() const { return isTurbo; }

bool SnakeGame::isGameOver() const { return gameOver; }

extern "C" void userInput(UserAction_t action, bool hold) {
  if (game) game->userInput(action, hold);
}

extern "C" GameInfo_t updateCurrentState() {
  return game ? game->updateCurrentState() : GameInfo_t();
}

extern "C" void initializeGame() {
  if (!game) game = new SnakeGame();
}

extern "C" void terminateGame() {
  if (game) {
    delete game;
    game = nullptr;
  }
}