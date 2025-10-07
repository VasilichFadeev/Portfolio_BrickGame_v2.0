#include "../../../brick_game/tetris/tetris_game.h"

void TetrisGame::placePiece() {
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (currentPiece.shape[i][j]) {
        int x = currentX + j;
        int y = currentY + i;
        if (x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1) {
          field[y][x] = QChar(L'█');
          colors[y][x] = "#000000";
        }
      }
}