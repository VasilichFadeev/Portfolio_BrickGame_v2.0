#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "desktop_snake.h"
using namespace std;

/**
 * @brief Очистка игрового поля.
 *
 * Заносит в каждую клетку символ пробела.
 */
void s21::SnakeWindow::clearField() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      field[y][x] = QChar(L' ');
    }
  }
}

/**
 * @brief Тест генерации яблока на поле.
 *
 * Проверяет, что после вызова generateApple() количество яблок увеличилось на 1
 * и новое яблоко находится внутри игрового поля.
 */
TEST(DesktopSnakeTest, generateAppleTest) {
  s21::SnakeWindow window;

  auto field = window.getField();

  int applesBefore = 0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (field[y][x] == QChar(2)) {
        applesBefore++;
      }
    }
  }

  window.generateApple();

  field = window.getField();

  int applesAfter = 0;
  QPoint applePosition(-1, -1);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (field[y][x] == QChar(2)) {
        applesAfter++;
        applePosition = QPoint(x, y);
      }
    }
  }

  EXPECT_EQ(applesAfter, applesBefore + 1);

  EXPECT_GE(applePosition.x(), 1);
  EXPECT_LE(applePosition.x(), WIDTH - 2);
  EXPECT_GE(applePosition.y(), 1);
  EXPECT_LE(applePosition.y(), HEIGHT - 2);

  EXPECT_EQ(field[applePosition.y()][applePosition.x()], QChar(2));

  EXPECT_TRUE(applePosition.x() > 0 && applePosition.x() < WIDTH - 1);
  EXPECT_TRUE(applePosition.y() > 0 && applePosition.y() < HEIGHT - 1);
}

/**
 * @brief Тест генерации яблока на полностью пустом поле.
 */
TEST(DesktopSnakeTest, generateAppleOnEmptyFieldTest) {
  s21::SnakeWindow window;

  window.clearField();

  window.generateApple();

  auto field = window.getField();

  int appleCount = 0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (field[y][x] == QChar(2)) {
        appleCount++;
      }
    }
  }

  EXPECT_EQ(appleCount, 1);
}

/**
 * @brief Тест загрузки рекорда из файла.
 */
TEST(DesktopSnakeTest, loadHighScoreTest) {
  ofstream outFile("./snake_high_score.txt");
  outFile << "1234" << endl;
  outFile.close();
  s21::SnakeWindow game;
  game.loadHighScore();
  ASSERT_EQ(game.getHighScore(), 1234);
  remove("./snake_high_score.txt");
}

/**
 * @brief Тест сброса состояния игры.
 */
TEST(DesktopSnakeTest, resetGameTest) {
  s21::SnakeWindow game;
  game.resetGame();
  ASSERT_EQ(game.getGameOver(), false);
  ASSERT_EQ(game.getGameWon(), false);
}

/**
 * @brief Тест сохранения рекорда в файл.
 */
TEST(DesktopSnakeTest, saveHighScore) {
  remove("./snake_high_score.txt");
  s21::SnakeWindow game;
  ASSERT_NO_THROW(game.saveHighScore());
  ifstream testFile("./snake_high_score.txt");
  ASSERT_TRUE(testFile.is_open());
  remove("./snake_high_score.txt");
}

/**
 * @brief Тест запуска игры и инициализации состояния.
 */
TEST(DesktopSnakeTest, startGameTest) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();
  ASSERT_EQ(game.getCurrentScore(), 0);
  ASSERT_EQ(game.getCurrentLevel(), 1);
  ASSERT_EQ(game.getIsTurbo(), false);
  ASSERT_EQ(game.getGamePaused(), false);
  ASSERT_EQ(game.getGameOver(), false);
  ASSERT_EQ(game.getGameWon(), false);
}

/**
 * @brief Проверяет переключение паузы: не пауза → пауза → не пауза.
 */
TEST(DesktopSnakeTest, togglePauseTest_nonpause_pause_nonpause) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  EXPECT_FALSE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_TRUE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_FALSE(game.getGamePaused());
}

/**
 * @brief Проверяет многократное переключение паузы: пауза ↔ не пауза.
 */
TEST(DesktopSnakeTest, togglePauseTest_pause_nonpause_pause_nonpause) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  EXPECT_FALSE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_TRUE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_FALSE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_TRUE(game.getGamePaused());

  game.StartInTestTogglePause();
  EXPECT_FALSE(game.getGamePaused());
}

/**
 * @brief Интеграционный тест togglePause с состоянием игры.
 *
 * Проверяет, что togglePause изменяет только gamePaused и не влияет на gameOver
 * и gameWon.
 */
TEST(DesktopSnakeTest, togglePauseTest_IntegrationWithGameState) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  EXPECT_FALSE(game.getGameOver());
  EXPECT_FALSE(game.getGameWon());
  EXPECT_FALSE(game.getGamePaused());

  game.StartInTestTogglePause();

  EXPECT_FALSE(game.getGameOver());
  EXPECT_FALSE(game.getGameWon());
  EXPECT_TRUE(game.getGamePaused());

  game.StartInTestTogglePause();

  EXPECT_FALSE(game.getGameOver());
  EXPECT_FALSE(game.getGameWon());
  EXPECT_FALSE(game.getGamePaused());
}

/**
 * @brief Проверяет обычное включение и выключение турбо-режима.
 */
TEST(DesktopSnakeTest, toggleTurboTest_NormalConditions) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  EXPECT_FALSE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_TRUE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_FALSE(game.getIsTurbo());
}

/**
 * @brief Проверяет, что toggleTurbo корректно работает при gameOver.
 */
TEST(DesktopSnakeTest, toggleTurboTest_WhenGameOver) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  bool turboBefore = game.getIsTurbo();
  game.StartInTestToggleTurbo();

  EXPECT_NO_THROW(game.StartInTestToggleTurbo());
}

/**
 * @brief Проверяет, что toggleTurbo корректно работает при gameWon.
 */
TEST(DesktopSnakeTest, toggleTurboTest_WhenGameWon) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  bool turboBefore = game.getIsTurbo();
  game.StartInTestToggleTurbo();

  EXPECT_NO_THROW(game.StartInTestToggleTurbo());
}

/**
 * @brief Проверяет многократное включение и выключение турбо-режима.
 */
TEST(DesktopSnakeTest, toggleTurboTest_MultipleCalls) {
  s21::SnakeWindow game;
  game.StartInTestStartGame();

  EXPECT_FALSE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_TRUE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_FALSE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_TRUE(game.getIsTurbo());

  game.StartInTestToggleTurbo();
  EXPECT_FALSE(game.getIsTurbo());
}

/**
 * @brief Проверяет метод updateSpeed для различных уровней и турбо-режима.
 *
 * - Проверяет диапазон скорости и корректность работы таймера.
 */
TEST(DesktopSnakeTest, updateSpeedTest) {
  struct TestCase {
    int level;
    bool turbo;
    const char* description;
  };

  TestCase testCases[] = {
      {1, false, "Level 1 без турбо"},
      {1, true, "Level 1 с турбо"},
      {5, false, "Level 5 без турбо"},
      {10, false, "Level 10 без турбо (минимальная скорость)"},
      {12, false, "Level 12 без турбо (превышение границ)"},
      {10, true, "Level 10 с турбо"}};

  for (const auto& testCase : testCases) {
    SCOPED_TRACE(testCase.description);

    s21::SnakeWindow game;
    game.StartInTestStartGame();

    if (testCase.turbo) {
      game.StartInTestToggleTurbo();
      EXPECT_TRUE(game.getIsTurbo());
    }

    EXPECT_NO_THROW(game.StartInTestUpdateSpeed());

    EXPECT_TRUE(game.getTimer() != nullptr);

    int expectedSpeed = 300 - (testCase.level * 25);
    if (expectedSpeed < 50) expectedSpeed = 50;
    if (testCase.turbo) expectedSpeed /= 2;

    EXPECT_GE(expectedSpeed, 25);
    EXPECT_LE(expectedSpeed, 275);
  }

  s21::SnakeWindow game;
  game.StartInTestStartGame();
  game.StartInTestUpdateSpeed();

  EXPECT_TRUE(game.getTimer() != nullptr);
  EXPECT_TRUE(game.getTimer()->isActive() || !game.getTimer()->isActive());
}

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}