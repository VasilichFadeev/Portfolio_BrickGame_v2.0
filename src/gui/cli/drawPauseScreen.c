#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Отображает сообщение о паузе на экране.
 */
void drawPauseScreen() {
  int center_y = HEIGHT / 2;
  int center_x = WIDTH / 2 - 3;

  attron(A_BOLD);
  mvprintw(center_y, center_x, "PAUSED");
  attroff(A_BOLD);
}