/**
 * @file turbo.cpp
 * @brief Реализация функции отображения турбо-режима.
 */
#include "../../brick_game/snake/snake/snake_terminal.h"

namespace s21 {
/**
 * @brief Отображает индикатор турбо-режима.
 *
 * Если турбо-режим активен, печатает надпись "TURBO" жёлтым цветом.
 */
void turbo() {
  if (game && game->getTurboState()) {
    attron(COLOR_PAIR(3));
    printw(" TURBO");
    attroff(COLOR_PAIR(3));
  }
  printw("\n");
}
}