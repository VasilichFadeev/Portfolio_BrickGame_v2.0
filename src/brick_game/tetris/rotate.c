#include "brick_game.h"

/**
 * @brief Поворачивает фигуру на 90° по часовой стрелке.
 *
 * @param shape Исходная матрица фигуры 4x4.
 * @param result Матрица, в которую записывается повернутая фигура.
 */
void rotate(int shape[4][4], int result[4][4]) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) result[x][3 - y] = shape[y][x];
}