#include "brick_game.h"

/**
 * @brief Очищает полностью заполненные линии на поле.
 *
 * @param points Указатель на счёт игрока (обновляется).
 * @param level Указатель на уровень (может увеличиться).
 * @param field Игровое поле.
 */
void clearLines(int *points, int *level, int field[HEIGHT][WIDTH]) {
  int lines_cleared = 0;
  for (int y = HEIGHT - 2; y > 0; y--) {
    int full = 1;
    for (int x = 1; x < WIDTH - 1; x++) {
      if (field[y][x] == 0) {
        full = 0;
        break;
      }
    }
    if (full) {
      for (int row = y; row > 0; row--) {
        for (int x = 1; x < WIDTH - 1; x++) {
          field[row][x] = field[row - 1][x];
        }
      }
      for (int x = 1; x < WIDTH - 1; x++) {
        field[0][x] = 0;
      }
      lines_cleared++;
      y++;
    }
  }

  if (lines_cleared > 0) {
    switch (lines_cleared) {
      case 1:
        *points += 100;
        break;
      case 2:
        *points += 300;
        break;
      case 3:
        *points += 700;
        break;
      case 4:
        *points += 1500;
        break;
    }
    if (*points / 600 > *level && *level < 10) {
      (*level)++;
    }
  }
}