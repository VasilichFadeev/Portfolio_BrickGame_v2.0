#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Отрисовывает текущую фигуру на игровом поле.
 *
 * @param t Фигура для отрисовки.
 */
void drawTetromino(Tetromino *t) {
  for (int y = 0; y < t->size; y++) {
    for (int x = 0; x < t->size; x++) {
      if (t->shape[y][x]) {
        wchar_t ch = L'█';
        cchar_t cch;
        setcchar(&cch, &ch, A_NORMAL, 0, NULL);
        attron(COLOR_PAIR(t->color_pair));
        mvadd_wch(t->y + y, t->x + x, &cch);
        attroff(COLOR_PAIR(t->color_pair));
      }
    }
  }
}