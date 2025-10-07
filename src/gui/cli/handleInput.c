#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Обрабатывает нажатия клавиш: перемещение фигуры, вращение, пауза.
 *
 * @param key Код нажатой клавиши.
 * @param t Текущая фигура.
 * @param paused Указатель на флаг паузы.
 * @param field Игровое поле для проверки коллизий.
 */
void handleInput(int key, Tetromino *t, int *paused, int field[HEIGHT][WIDTH]) {
  int rotated[4][4];
  switch (key) {
    case ' ':
      *paused = !(*paused);
      break;
    case KEY_LEFT:
      if (!(*paused) && !checkCollision(t->x - 1, t->y, t->shape, field))
        t->x--;
      break;
    case KEY_RIGHT:
      if (!(*paused) && !checkCollision(t->x + 1, t->y, t->shape, field))
        t->x++;
      break;
    case KEY_DOWN:
      if (!(*paused) && !checkCollision(t->x, t->y + 1, t->shape, field))
        t->y++;
      break;
    case KEY_UP:
      if (!(*paused)) {
        rotate(t->shape, rotated);
        if (!checkCollision(t->x, t->y, rotated, field))
          for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++) t->shape[y][x] = rotated[y][x];
      }
      break;
  }
}