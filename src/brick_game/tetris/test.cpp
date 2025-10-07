#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "tetris_game.h"
using namespace std;

TEST(DesktopTetrisTest, loadHighScore) {
  ofstream outFile("./tetris_high_score.txt");
  outFile << "1234" << endl;
  outFile.close();

  s21::TetrisGame game;
  game.loadHighScore();

  ASSERT_EQ(game.getHighScore(), 1234);

  remove("./tetris_high_score.txt");
}

TEST(DesktopTetrisTest, saveHighScore) {
  remove("./tetris_high_score.txt");
  s21::TetrisGame game;

  game.score = 1000;
  game.saveHighScore();

  ifstream testFile("./tetris_high_score.txt");
  ASSERT_TRUE(testFile.is_open());

  int savedHighScore;
  testFile >> savedHighScore;
  EXPECT_EQ(savedHighScore, 1000);

  testFile.close();
  remove("./tetris_high_score.txt");
}

TEST(DesktopTetrisTest, saveHighScoreWhenNotNewRecord) {
  ofstream outFile("./tetris_high_score.txt");
  outFile << "5000" << endl;
  outFile.close();

  s21::TetrisGame game;
  game.loadHighScore();

  game.score = 1000;
  game.saveHighScore();

  ifstream testFile("./tetris_high_score.txt");
  ASSERT_TRUE(testFile.is_open());

  int savedHighScore;
  testFile >> savedHighScore;
  EXPECT_EQ(savedHighScore, 5000);

  testFile.close();
  remove("./tetris_high_score.txt");
}

TEST(DesktopTetrisTest, getSpeedReturnsCorrectValue) {
  s21::TetrisGame game;

  ASSERT_EQ(game.getSpeed(), 400);
}

TEST(DesktopTetrisTest, isPausedReturnsCorrectState) {
  s21::TetrisGame game;

  ASSERT_FALSE(game.isPaused());
}

TEST(DesktopTetrisTest, spawnPieceResetsPositionAndSelectsNewPiece) {
  s21::TetrisGame game;

  Piece oldNextPiece = game.getNextPiece();
  int oldX = game.getCurrentX();
  int oldY = game.getCurrentY();

  game.spawnPiece();

  ASSERT_EQ(game.getCurrentX(), 4);
  ASSERT_EQ(game.getCurrentY(), 1);
}

TEST(DesktopTetrisTest, isValidReturnsTrueForValidPosition) {
  s21::TetrisGame game;

  int simpleShape[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};

  ASSERT_TRUE(game.isValid(simpleShape, 4, 1));
}

TEST(DesktopTetrisTest, isValidReturnsFalseForLeftWallCollision) {
  s21::TetrisGame game;

  int lineShape[4][4] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  ASSERT_FALSE(game.isValid(lineShape, -1, 1));
}

TEST(DesktopTetrisTest, isValidReturnsFalseForRightWallCollision) {
  s21::TetrisGame game;

  int lineShape[4][4] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  ASSERT_FALSE(game.isValid(lineShape, 8, 1));
}

TEST(DesktopTetrisTest, isValidReturnsFalseForBottomCollisionPrecise) {
  s21::TetrisGame game;

  int tallShape[4][4] = {
      {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};

  ASSERT_FALSE(game.isValid(tallShape, 4, 18));
}

TEST(DesktopTetrisTest, checkLinesTest) {
  s21::TetrisGame game;

  const int testY = 5;  // произвольная координата Y для теста

  // Заполняем одну полную линию блоками
  for (int x = 1; x < game.getWidth() - 1; ++x) {
    game.field[testY][x] = QChar(L'█');
    game.colors[testY][x] = "#FF0000";
  }

  // Заполнение линии
  game.field[testY + 1][2] = QChar(L'█');
  game.colors[testY + 1][2] = "#00FF00";

  // Сохраняем начальный счет
  int initialScore = game.score;

  game.checkLines();

  // Проверка, что полная линия удалена
  for (int x = 1; x < game.getWidth() - 1; ++x) {
    EXPECT_EQ(game.field[testY][x], QChar(' '));
    EXPECT_EQ(game.colors[testY][x], "#FFFFFF");
  }

  // Проверка, что неполная линия осталась на месте
  EXPECT_EQ(game.field[testY + 1][2], QChar(L'█'));
  EXPECT_EQ(game.colors[testY + 1][2], "#00FF00");

  // Проверка начисления очков
  EXPECT_EQ(game.score, initialScore + 100);
}

TEST(DesktopTetrisTest, checkMultipleLinesTest) {
  s21::TetrisGame game;

  // Подготавливаем тестовые данные - заполняем 4 полные линии
  const int startY = 10;

  for (int lines = 0; lines < 4; ++lines) {
    for (int x = 1; x < game.getWidth() - 1; ++x) {
      game.field[startY + lines][x] = QChar(L'█');
      game.colors[startY + lines][x] = "#0000FF";
    }
  }

  int initialScore = game.score;
  game.checkLines();

  // Проверка, что все 4 линии удалены
  for (int lines = 0; lines < 4; ++lines) {
    for (int x = 1; x < game.getWidth() - 1; ++x) {
      EXPECT_EQ(game.field[startY + lines][x], QChar(' '));
      EXPECT_EQ(game.colors[startY + lines][x], "#FFFFFF");
    }
  }

  // Проверка начисления 1500 очков за 4 линии
  EXPECT_EQ(game.score, initialScore + 1500);
}

TEST(DesktopTetrisTest, checkNoLinesTest) {
  s21::TetrisGame game;

  // Создание поля без полных линий
  for (int y = 1; y < game.getHeight() - 1; ++y) {
    for (int x = 1; x < game.getWidth() - 1; ++x) {
      game.field[y][x] = QChar(' ');
      game.colors[y][x] = "#FFFFFF";
    }
  }

  // Добавление нескольких случайных блоков
  game.field[5][3] = QChar(L'█');
  game.field[7][5] = QChar(L'█');

  int initialScore = game.score;
  game.checkLines();

  // Проверка, что счёт не изменился
  EXPECT_EQ(game.score, initialScore);

  // Проверка, что блоки остались на месте
  EXPECT_EQ(game.field[5][3], QChar(L'█'));
  EXPECT_EQ(game.field[7][5], QChar(L'█'));
}

TEST(DesktopTetrisTest, scoreForTwoLines) {
  s21::TetrisGame game;

  int initialScore = game.score;

  const int line1 = 15;
  const int line2 = 17;

  for (int x = 1; x < game.getWidth() - 1; ++x) {
    game.field[line1][x] = QChar(L'█');
  }

  for (int x = 1; x < game.getWidth() - 1; ++x) {
    game.field[line2][x] = QChar(L'█');
  }

  game.checkLines();

  EXPECT_EQ(game.score, initialScore + 300);
}

TEST(DesktopTetrisTest, scoreForThreeLines) {
  s21::TetrisGame game;

  int initialScore = game.score;

  const int line1 = 14;
  const int line2 = 16;
  const int line3 = 18;

  for (int x = 1; x < game.getWidth() - 1; ++x) {
    game.field[line1][x] = QChar(L'█');
    game.field[line2][x] = QChar(L'█');
    game.field[line3][x] = QChar(L'█');
  }

  game.checkLines();

  EXPECT_EQ(game.score, initialScore + 700);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}