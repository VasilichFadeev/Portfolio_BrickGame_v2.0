#include "../../../brick_game/tetris/tetris_game.h"
#include <QApplication> 

void TetrisGame::userInput(UserAction_t action) {
  int newX = currentX;
  int newY = currentY;
  Piece temp = currentPiece;
  int tempShape[4][4];
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j) tempShape[i][j] = temp.shape[i][j];

  switch (action) {
    case Left:
      newX--;
      break;
    case Right:
      newX++;
      break;
    case Down:
      newY++;
      break;
    case Up: {
      int rotated[4][4];
      for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) rotated[i][j] = tempShape[3 - j][i];
      if (isValid(rotated, currentX, currentY)) {
        for (int i = 0; i < 4; ++i)
          for (int j = 0; j < 4; ++j) temp.shape[i][j] = rotated[i][j];
      }
      break;
    }
    case Pause:
      pause = !pause;
      return;
    case Terminate:
      QApplication::quit();
      break;
    default:
      break;
  }

  if (!pause && isValid(temp.shape, newX, newY)) {
    currentX = newX;
    currentY = newY;
    currentPiece = temp;
  }
}