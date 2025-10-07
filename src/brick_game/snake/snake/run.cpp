#include "snake_terminal.h"

void run(bool &running, int &ch, bool &paused) {
  while (running) {
    inputHandler(paused, running);
    if (!running) break;
    GameInfo_t info = updateCurrentState();
    clear();
    printw("Score: %d  Level: %d  High: %d", info.score, info.level,
           info.high_score);
    turbo();
    drawField(paused, info);

    printw("\nControls: Arrows - move, Space - pause, E - turbo, Q - quit");

    if (paused) {
      printw("\nPress SPACE to continue...");
      nodelay(stdscr, FALSE);
      while ((ch = getch()) != ' ') {
        if (ch == 'q' || ch == 'Q') {
          running = false;
          break;
        }
      }
      nodelay(stdscr, TRUE);
      if (running) {
        paused = false;
        userInput(Pause, false);
      }
    } else if (game && game->isGameOver()) {
      printw("\nPress Q to quit...");
      nodelay(stdscr, FALSE);
      while ((ch = getch()) != 'q' && ch != 'Q') {
      }
      nodelay(stdscr, TRUE);
      running = false;
    } else {
      timeout(info.speed);
    }

    refresh();
  }
}