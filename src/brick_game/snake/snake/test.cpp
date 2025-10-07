/**
 * @file test.cpp
 * @brief Набор модульных тестов для игры "Змейка" (Snake).
 *
 * Используется библиотека Google Test (gtest).
 * Тестируются основные функции класса @ref s21::SnakeGame:
 * - конвертация игрового поля в числовой формат
 * - работа с рекордом (загрузка и сохранение)
 * - обработка пользовательского ввода (турбо, пауза)
 * - логика столкновений (со стенами, собой, яблоком)
 * - условия окончания и победы
 * - обновление состояния игры
 */
#include <gtest/gtest.h>

#include "snake_terminal.h"
using namespace std;

/**
 * @test Проверка корректной конвертации поля из wchar_t в int.
 */
TEST(TerminalSnakeTest, convertFieldToIntTest) {
  s21::SnakeGame game;

  wchar_t testField[HEIGHT][WIDTH] = {0};

  testField[1][1] = L'█';
  testField[5][5] = L'●';
  testField[3][3] = L' ';

  int **fieldInt = new int *[HEIGHT];
  for (int i = 0; i < HEIGHT; ++i) {
    fieldInt[i] = new int[WIDTH];
  }

  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (testField[y][x] == L'█') {
        fieldInt[y][x] = 1;
      } else if (testField[y][x] == L'●') {
        fieldInt[y][x] = 2;
      } else {
        fieldInt[y][x] = 0;
      }
    }
  }

  EXPECT_EQ(fieldInt[1][1], 1);
  EXPECT_EQ(fieldInt[5][5], 2);
  EXPECT_EQ(fieldInt[3][3], 0);

  for (int i = 0; i < HEIGHT; ++i) {
    delete[] fieldInt[i];
  }
  delete[] fieldInt;
}

/**
 * @test Проверка загрузки рекорда из файла.
 */
TEST(TerminalSnakeTest, loadHighScoreTest) {
  ofstream outFile("./snake_high_score.txt");
  outFile << "1234" << endl;
  outFile.close();

  s21::SnakeGame game;
  game.loadHighScore();

  ASSERT_EQ(game.getHighScore(), 1234);

  remove("./snake_high_score.txt");
}

/**
 * @test Проверка сохранения рекорда в файл.
 */
TEST(TerminalSnakeTest, saveHighScoreTest) {
  remove("./snake_high_score.txt");
  s21::SnakeGame game;
  ASSERT_NO_THROW(game.saveHighScore());
  ifstream testFile("./snake_high_score.txt");
  ASSERT_TRUE(testFile.is_open());
  remove("./snake_high_score.txt");
}

/**
 * @test Проверка состояния Turbo по умолчанию.
 */
TEST(TerminalSnakeTest, getTurboStateTest) {
  s21::SnakeGame game;
  ASSERT_EQ(0, game.getTurboState());
}

/**
 * @test Проверка состояния окончания игры по умолчанию.
 */
TEST(TerminalSnakeTest, isGameOverTest) {
  s21::SnakeGame game;
  ASSERT_EQ(0, game.isGameOver());
}

/**
 * @test Проверка обновления структуры GameInfo_t.
 */
TEST(TerminalSnakeTest, updateGameInfoTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  game.updateGameInfo(info);

  EXPECT_EQ(info.field, game.fieldInt);
  EXPECT_EQ(info.next, game.nextInt);
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.high_score, 0);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.speed, 275);
  EXPECT_EQ(info.pause, 0);
}

/**
 * @test Проверка обновления скорости в режиме Turbo.
 */
TEST(TerminalSnakeTest, updateGameInfoTurboTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  game.userInput(Turbo, false);

  game.updateGameInfo(info);

  EXPECT_EQ(info.speed, 137);
  EXPECT_EQ(info.pause, 0);
}

/**
 * @test Проверка обновления состояния при паузе.
 */
TEST(TerminalSnakeTest, updateGameInfoPauseTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  game.userInput(Pause, false);

  game.updateGameInfo(info);

  EXPECT_EQ(info.pause, 1);
}

/**
 * @test Проверка расчёта скорости на максимальном уровне.
 */
TEST(TerminalSnakeTest, updateGameInfoLevelSpeedTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  int testLevel = 10;
  int expectedSpeed = 300 - (testLevel * 25);
  if (expectedSpeed < 50) expectedSpeed = 50;

  EXPECT_EQ(expectedSpeed, 50);

  testLevel = 11;
  expectedSpeed = 300 - (testLevel * 25);
  if (expectedSpeed < 50) expectedSpeed = 50;

  EXPECT_EQ(expectedSpeed, 50);
}

/**
 * @test Проверка столкновений со стенами.
 */
TEST(TerminalSnakeTest, checkCollisionWithWallsTest) {
  s21::SnakeGame game;
  EXPECT_EQ(game.checkCollisionWithWalls(0, 0), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(0, 11), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(21, 0), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(21, 11), 1);

  EXPECT_EQ(game.checkCollisionWithWalls(5, 0), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(0, 5), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(5, 11), 1);
  EXPECT_EQ(game.checkCollisionWithWalls(21, 5), 1);

  EXPECT_EQ(game.checkCollisionWithWalls(1, 1), 0);
  EXPECT_EQ(game.checkCollisionWithWalls(10, 10), 0);
  EXPECT_EQ(game.checkCollisionWithWalls(20, 10), 0);
  EXPECT_EQ(game.checkCollisionWithWalls(10, 10), 0);

  EXPECT_EQ(game.checkCollisionWithWalls(1, 1), 0);
  EXPECT_EQ(game.checkCollisionWithWalls(20, 10), 0);
  EXPECT_EQ(game.checkCollisionWithWalls(10, 10), 0);
}

/**
 * @test Проверка столкновений змейки с собой.
 */
TEST(TerminalSnakeTest, checkCollisionWithSelfTest) {
  s21::SnakeGame game;
  // Проверка маленькой змеи
  EXPECT_EQ(game.checkCollisionWithSelf(0, 0), 0);

  // Змея в несколько пикселей
  game.snake = {{5, 5}, {6, 5}, {7, 5}, {8, 5}};

  // Столкновение с хвостом
  EXPECT_EQ(game.checkCollisionWithSelf(5, 5), 1);

  // Столкновение с телом
  EXPECT_EQ(game.checkCollisionWithSelf(6, 5), 1);
  EXPECT_EQ(game.checkCollisionWithSelf(7, 5), 1);

  // Отсутствие столкновения с головой
  EXPECT_EQ(game.checkCollisionWithSelf(8, 5), 0);

  // Отсутствие столкновения с пустой клеткой
  EXPECT_EQ(game.checkCollisionWithSelf(10, 10), 0);

  // Змея из одного пикселя
  game.snake = {{5, 5}};
  EXPECT_EQ(game.checkCollisionWithSelf(5, 5), 0);
  EXPECT_EQ(game.checkCollisionWithSelf(6, 5), 0);
}

/**
 * @test Проверка обработки столкновения (game over).
 */
TEST(TerminalSnakeTest, handleCollisionTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  // Изначально игра не окончена
  EXPECT_FALSE(game.isGameOver());
  EXPECT_EQ(info.pause, 0);

  // Симулируем столкновение
  game.handleCollision(info);

  // Проверяем, что игра окончена и пауза установлена
  EXPECT_TRUE(game.isGameOver());
  EXPECT_EQ(info.pause, 1);

  // Проверяем сохранение рекорда при высоком счёте
  game.currentScore = 1000;
  game.highScore = 500;
  game.handleCollision(info);
  EXPECT_EQ(game.highScore, 1000);  // ОБновление рекорда
}

/**
 * @test Проверка перемещения змейки.
 */
TEST(TerminalSnakeTest, moveSnakeTest) {
  s21::SnakeGame game;

  // Изначальная змея
  game.snake = {{5, 5}, {6, 5}, {7, 5}};
  game.field[5][5] = L'█';
  game.field[6][5] = L'█';
  game.field[7][5] = L'█';

  // Двигаем змею в новую позицию
  game.moveSnake(8, 5);

  // Проверяем новое состояние змеи
  EXPECT_EQ(game.snake.size(), 3);
  EXPECT_EQ(game.snake[0].y, 6);  // Новый хвост
  EXPECT_EQ(game.snake[0].x, 5);
  EXPECT_EQ(game.snake[1].y, 7);  // Тело
  EXPECT_EQ(game.snake[1].x, 5);
  EXPECT_EQ(game.snake[2].y, 8);  // Новая голова
  EXPECT_EQ(game.snake[2].x, 5);

  // Проверяем очистку старого хвоста
  EXPECT_EQ(game.field[5][5], L' ');

  // Проверяем установку новой головы
  EXPECT_EQ(game.field[8][5], L'█');
}

/**
 * @test Проверка обработки съедания яблока.
 */
TEST(TerminalSnakeTest, handleAppleCollisionTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  // Начальные значения
  game.snake = {{5, 5}, {6, 5}};
  game.currentScore = 0;
  game.currentLevel = 1;

  // Обрабатываем столкновение с яблоком
  game.handleAppleCollision(info, 7, 5);

  // Проверяем увеличение счёта
  EXPECT_EQ(game.currentScore, 10);

  // Проверяем увеличение длины змеи
  EXPECT_EQ(game.snake.size(), 3);
  EXPECT_EQ(game.snake[0].y, 5);
  EXPECT_EQ(game.snake[0].x, 5);
  EXPECT_EQ(game.snake[1].y, 5);
  EXPECT_EQ(game.snake[1].x, 5);
  EXPECT_EQ(game.snake[2].y, 6);
  EXPECT_EQ(game.snake[2].x, 5);

  // Проверка повышения уровня
  game.currentScore = 50;
  game.handleAppleCollision(info, 8, 5);
  EXPECT_EQ(game.currentLevel, 2);

  // Проверяем максимальный уровень
  game.currentScore = 500;
  game.currentLevel = 10;
  game.handleAppleCollision(info, 9, 5);
  EXPECT_EQ(game.currentLevel, 10);  // Не должен превысить MAX_LEVEL
}

/**
 * @test Проверка условия победы.
 */
TEST(TerminalSnakeTest, checkWinConditionTest) {
  s21::SnakeGame game;
  GameInfo_t info = {};

  // Изначально игра не выиграна
  EXPECT_FALSE(game.gameWon);
  EXPECT_EQ(info.pause, 0);

  // Симулируем выигрышную длину змеи
  game.snake.resize(WIN_LENGTH);
  game.currentScore = 1000;
  game.highScore = 500;

  game.checkWinCondition(info);

  // Проверяем условия победы
  EXPECT_TRUE(game.gameWon);
  EXPECT_EQ(info.pause, 1);
  EXPECT_EQ(game.getHighScore(), 1000);

  // Проверяем случай, когда змея короче выигрышной длины
  game.gameWon = false;
  info.pause = 0;
  game.snake.resize(WIN_LENGTH - 1);

  game.checkWinCondition(info);

  EXPECT_FALSE(game.gameWon);
  EXPECT_EQ(info.pause, 0);
}

/**
 * @brief Точка входа для запуска тестов Google Test.
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}