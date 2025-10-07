#include "../../brick_game/snake/snake/snake_terminal.h"

void turbo() {
  if (game && game->getTurboState()) {
    attron(COLOR_PAIR(3));
    printw(" TURBO");
    attroff(COLOR_PAIR(3));
  }
  printw("\n");
}