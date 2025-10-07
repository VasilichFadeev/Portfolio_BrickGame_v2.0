#include "brick_game.h"

/**
 * @brief Сливает текущую фигуру с игровым полем (фиксирует её на поле).
 *
 * @param t Указатель на фигуру.
 * @param field Игровое поле.
 */
void mergeTetromino(const Tetromino *t, int field[HEIGHT][WIDTH]) {
  for (int y = 0; y < t->size; y++) {
    for (int x = 0; x < t->size; x++) {
      if (t->shape[y][x]) {
        field[t->y + y][t->x + x] = 1;
      }
    }
  }
}