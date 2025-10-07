#include "../../brick_game/tetris/brick_game.h"

void drawNextTetromino(Tetromino *t) {
  int offsetX = WIDTH + 3;
  int offsetY = 7;

  mvprintw(offsetY - 2, offsetX, "Next:");

  for (int y = 0; y < t->size; y++) {
    for (int x = 0; x < t->size; x++) {
      if (t->shape[y][x]) {
        wchar_t ch = L'█';
        cchar_t cch;
        setcchar(&cch, &ch, A_NORMAL, 0, NULL);
        attron(COLOR_PAIR(t->color_pair));
        mvadd_wch(offsetY + y, offsetX + x, &cch);
        attroff(COLOR_PAIR(t->color_pair));
      }
    }
  }
}