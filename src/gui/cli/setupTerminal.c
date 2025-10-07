#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Настраивает консоль для игры: инициализация ncurses, цвета, режим
 * ввода.
 */
void setupTerminal() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(100);
  srand(time(NULL));
}