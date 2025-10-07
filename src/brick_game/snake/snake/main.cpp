/**
 * @file main.cpp
 * @brief Точка входа в консольную версию игры Snake.
 */
#include "snake_terminal.h"

/**
 * @brief Основная функция запуска игры Snake в консоли.
 *
 * Настраивает окружение с использованием `ncurses`,
 * инициализирует цвета, запускает игровой цикл
 * через `s21::run()` и завершает работу после выхода из игры.
 *
 * @return Код завершения (0 при успешном завершении).
 */

int main() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);

  s21::initializeGame();

  bool running = true;
  bool paused = false;
  int ch;

  s21::run(running, ch, paused);

  s21::terminateGame();
  endwin();
  return 0;
}