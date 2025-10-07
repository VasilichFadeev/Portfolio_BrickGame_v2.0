#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Отрисовывает весь игровой экран: поле, фигуру, следующую фигуру, счёт
 * и уровень.
 *
 * @param field Игровое поле.
 * @param current Текущая фигура.
 * @param next Следующая фигура.
 * @param points Текущий счёт.
 * @param level Текущий уровень.
 * @param highScore Рекорд.
 * @param paused Флаг паузы.
 * @param first_move Флаг первого хода (чтобы фигура не отображалась сразу).
 */
void renderGame(int field[HEIGHT][WIDTH], Tetromino *current, Tetromino *next,
                int points, int level, int highScore, int paused,
                int first_move) {
  clear();
  int current_speed = calculateSpeed(level);
  drawField(points, level, current_speed, highScore, field);
  drawTetromino(current);
  if (!first_move) drawNextTetromino(next);
  if (paused) drawPauseScreen();
  refresh();
}