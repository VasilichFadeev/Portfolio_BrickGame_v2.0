#include "brick_game.h"

/**
 * @brief Главная функция игры: инициализация, игровой цикл и завершение.
 */
int main() {
  setupTerminal();
  setupColors();

  int field[HEIGHT][WIDTH] = {0};
  Tetromino current, next;
  int paused = 0, points = 0, level = 0, tick = 0, game_over = 0,
      first_move = 1;
  int highScore = readHighScore();

  initNextTetromino(&next);
  spawnTetromino(&current, &next);

  while (!game_over) {
    renderGame(field, &current, &next, points, level, highScore, paused,
               first_move);

    int ch = getch();
    if (handleQuit(ch)) break;
    if (first_move && ch != ERR) first_move = 0;

    handleInput(ch, &current, &paused, field);

    if (!paused) {
      game_over = handleTick(&tick, &current, &next, field, &points, &level,
                             &highScore);
    }

    sleepWithLevel(level);
  }

  endwin();
  return 0;
}
