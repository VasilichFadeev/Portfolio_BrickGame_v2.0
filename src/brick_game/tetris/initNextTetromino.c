#include "brick_game.h"

/**
 * @brief Инициализирует следующую фигуру с случайной формой и цветом.
 *
 * @param t Указатель на структуру Tetromino для следующей фигуры.
 */
void initNextTetromino(Tetromino *t) {
  int id = rand() % 7;
  t->x = 0;
  t->y = 0;
  t->size = 4;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) t->shape[y][x] = shapes[id][y][x];

  const int colors[] = {PINK_PAIR,  RED_PAIR,  ORANGE_PAIR, YELLOW_PAIR,
                        GREEN_PAIR, BLUE_PAIR, PURPLE_PAIR};
  t->color_pair = colors[id];
}