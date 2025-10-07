#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "desktop_snake.h"
using namespace std;

void s21::SnakeWindow::clearField() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      field[y][x] = QChar(L' ');
    }
  }
}

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

// Тест для проверки генерации яблока на полностью пустом поле
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

TEST(DesktopSnakeTest, loadHighScoreTest) {
  ofstream outFile("./snake_high_score.txt");
  outFile << "1234" << endl;
  outFile.close();
  s21::SnakeWindow game;
  game.loadHighScore();
  ASSERT_EQ(game.getHighScore(), 1234);
  remove("./snake_high_score.txt");
}

TEST(DesktopSnakeTest, resetGameTest) {
  s21::SnakeWindow game;
  game.resetGame();
  ASSERT_EQ(game.getGameOver(), false);
  ASSERT_EQ(game.getGameWon(), false);
}

TEST(DesktopTetrisTest, saveHighScore) {
  remove("./snake_high_score.txt");
  s21::SnakeWindow game;
  ASSERT_NO_THROW(game.saveHighScore());
  ifstream testFile("./snake_high_score.txt");
  ASSERT_TRUE(testFile.is_open());
  remove("./snake_high_score.txt");
}

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}