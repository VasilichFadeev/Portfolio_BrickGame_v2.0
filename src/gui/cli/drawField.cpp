#include "../../brick_game/snake/snake/snake_terminal.h"

/**
 * @brief Отрисовывает игровое поле, рамку, блоки, счёт, уровень и рекорд.
 *
 * @param points Текущий счёт.
 * @param level Текущий уровень.
 * @param speed Текущая скорость игры.
 * @param highScore Рекорд.
 * @param field Игровое поле.
 */
namespace s21 {
void drawField(bool &paused, GameInfo_t &info) {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if ((paused || (game && game->isGameOver())) && y == HEIGHT / 2 &&
          x == (WIDTH - 8) / 2) {
        printw(game->isGameOver() ? "GAME OVER" : " PAUSED ");
        x += game->isGameOver() ? 8 : 7;
        continue;
      }

      switch (info.field[y][x]) {
        case 2:
          attron(COLOR_PAIR(1));
          addwstr(L"●");
          attroff(COLOR_PAIR(1));
          break;
        case 1:
          attron(COLOR_PAIR(2));
          addwstr(L"█");
          attroff(COLOR_PAIR(2));
          break;
        default:
          if (x == 0 && y == 0)
            addwstr(L"┌");
          else if (x == WIDTH - 1 && y == 0)
            addwstr(L"┐");
          else if (x == 0 && y == HEIGHT - 1)
            addwstr(L"└");
          else if (x == WIDTH - 1 && y == HEIGHT - 1)
            addwstr(L"┘");
          else if (y == 0 || y == HEIGHT - 1)
            addwstr(L"─");
          else if (x == 0 || x == WIDTH - 1)
            addwstr(L"│");
          else
            addwstr(L" ");
      }
    }
    printw("\n");
  }
}
}