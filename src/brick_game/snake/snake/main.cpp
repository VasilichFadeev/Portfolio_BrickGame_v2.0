#include "snake_terminal.h"

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

  initializeGame();

  bool running = true;
  bool paused = false;
  int ch;

  run(running, ch, paused);

  terminateGame();
  endwin();
  return 0;
}