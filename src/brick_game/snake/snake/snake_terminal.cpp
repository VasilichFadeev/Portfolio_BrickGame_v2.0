#include "snake_terminal.h"

namespace s21 {
/**
 * @brief Глобальный указатель на объект игры.
 *
 * Используется для управления состоянием игры через C-интерфейс.
 */
SnakeGame* game = nullptr;

/**
 * @brief Конструктор игры "Змейка".
 *
 * Выполняет:
 * - выделение памяти под игровые поля (`fieldInt`, `nextInt`)
 * - инициализацию направления движения
 * - сброс игровых флагов
 * - загрузку рекорда
 * - подготовку поля (рамка, змейка, яблоко)
 */
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

/**
 * @brief Деструктор игры "Змейка".
 *
 * Освобождает память, выделенную под игровые поля.
 */
SnakeGame::~SnakeGame() {
  for (int i = 0; i < HEIGHT; ++i) {
    delete[] fieldInt[i];
    delete[] nextInt[i];
  }
  delete[] fieldInt;
  delete[] nextInt;
}

/**
 * @brief Обновляет структуру с текущим состоянием игры.
 *
 * @param info ссылка на структуру с игровыми данными
 */
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

/**
 * @brief Проверка столкновения со стенами.
 *
 * @param newY новая координата Y головы змейки
 * @param newX новая координата X головы змейки
 * @return true если произошло столкновение
 */
bool SnakeGame::checkCollisionWithWalls(int newY, int newX) {
  return (newX <= 0 || newX >= WIDTH - 1 || newY <= 0 || newY >= HEIGHT - 1);
}

/**
 * @brief Проверка столкновения с телом змейки.
 *
 * @param newY новая координата Y головы змейки
 * @param newX новая координата X головы змейки
 * @return true если змейка врезалась в себя
 */
bool SnakeGame::checkCollisionWithSelf(int newY, int newX) {
  for (size_t i = 0; i < snake.size() - 1; ++i) {
    if (snake[i].x == newX && snake[i].y == newY) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Обработка столкновения (игра окончена).
 *
 * @param info ссылка на структуру с игровыми данными
 */
void SnakeGame::handleCollision(GameInfo_t& info) {
  gameOver = true;
  if (currentScore > highScore) {
    highScore = currentScore;
    saveHighScore();
  }
  info.pause = 1;
}

/**
 * @brief Перемещает змейку на новую позицию.
 *
 * @param newY новая координата Y головы
 * @param newX новая координата X головы
 */
void SnakeGame::moveSnake(int newY, int newX) {
  SnakeSegment tail = snake.front();
  field[tail.y][tail.x] = L' ';
  snake.erase(snake.begin());
  snake.push_back({newY, newX});
  field[newY][newX] = L'█';
}

/**
 * @brief Обрабатывает поедание яблока.
 *
 * Увеличивает счёт, может повысить уровень,
 * удлиняет змейку и создаёт новое яблоко.
 *
 * @param info ссылка на структуру с игровыми данными
 * @param newY координата Y головы
 * @param newX координата X головы
 */
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

/**
 * @brief Проверка условия победы.
 *
 * Победа наступает, если змейка достигла длины @ref WIN_LENGTH.
 *
 * @param info ссылка на структуру с игровыми данными
 */
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

/**
 * @brief Возвращает состояние режима Turbo.
 */
bool SnakeGame::getTurboState() const { return isTurbo; }

/**
 * @brief Проверяет, окончена ли игра.
 */
bool SnakeGame::isGameOver() const { return gameOver; }

/**
 * @brief Обрабатывает ввод пользователя (C-интерфейс).
 *
 * @param action действие (см. @ref UserAction_t)
 * @param hold true, если кнопка удерживается
 */
extern "C" void userInput(UserAction_t action, bool hold) {
  if (game) game->userInput(action, hold);
}

/**
 * @brief Обновляет текущее состояние игры (C-интерфейс).
 *
 * @return структура с игровыми данными
 */
extern "C" GameInfo_t updateCurrentState() {
  return game ? game->updateCurrentState() : GameInfo_t();
}

/**
 * @brief Инициализирует игру (C-интерфейс).
 *
 * Создаёт объект SnakeGame.
 */
extern "C" void initializeGame() {
  if (!game) game = new SnakeGame();
}

/**
 * @brief Завершает игру (C-интерфейс).
 *
 * Удаляет объект SnakeGame и освобождает память.
 */
extern "C" void terminateGame() {
  if (game) {
    delete game;
    game = nullptr;
  }
}
}  // namespace s21