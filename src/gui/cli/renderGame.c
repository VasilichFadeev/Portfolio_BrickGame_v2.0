#include "../../brick_game/tetris/brick_game.h"

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