#include "brick_game.h"

/**
 * @brief Спавнит новую фигуру в центре поля и инициализирует следующую.
 *
 * @param current Текущая фигура (становится активной).
 * @param next Следующая фигура (будет отображаться на предпросмотре).
 */
void spawnTetromino(Tetromino *current, Tetromino *next) {
  *current = *next;
  current->x = WIDTH / 2 - 2;
  current->y = 1;

  initNextTetromino(next);
}