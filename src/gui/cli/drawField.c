#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Отрисовывает игровое поле с рамкой и блоками, а также счёт, уровень,
 * скорость и рекорд.
 *
 * @param points Текущий счёт.
 * @param level Текущий уровень.
 * @param speed Текущая скорость игры.
 * @param highScore Рекорд игрока.
 * @param field Игровое поле (матрица HEIGHT x WIDTH, где 0 — пусто, >0 — блок).
 */
void drawField(int points, int level, int speed, int highScore,
               int field[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      wchar_t ch = field[y][x] ? L'█' : L' ';
      cchar_t cch;
      setcchar(&cch, &ch, A_NORMAL, 0, NULL);
      mvadd_wch(y, x, &cch);
    }
  }

  for (int y = 0; y < HEIGHT; y++) {
    wchar_t border = L'│';
    cchar_t cch;
    setcchar(&cch, &border, A_NORMAL, 0, NULL);
    mvadd_wch(y, 0, &cch);
    mvadd_wch(y, WIDTH - 1, &cch);
  }
  for (int x = 0; x < WIDTH; x++) {
    wchar_t border = L'─';
    cchar_t cch;
    setcchar(&cch, &border, A_NORMAL, 0, NULL);
    mvadd_wch(0, x, &cch);
    mvadd_wch(HEIGHT - 1, x, &cch);
  }

  wchar_t corners[4] = {L'┌', L'┐', L'└', L'┘'};
  cchar_t corner_cch;
  setcchar(&corner_cch, &corners[0], A_NORMAL, 0, NULL);
  mvadd_wch(0, 0, &corner_cch);
  setcchar(&corner_cch, &corners[1], A_NORMAL, 0, NULL);
  mvadd_wch(0, WIDTH - 1, &corner_cch);
  setcchar(&corner_cch, &corners[2], A_NORMAL, 0, NULL);
  mvadd_wch(HEIGHT - 1, 0, &corner_cch);
  setcchar(&corner_cch, &corners[3], A_NORMAL, 0, NULL);
  mvadd_wch(HEIGHT - 1, WIDTH - 1, &corner_cch);

  mvprintw(1, WIDTH + 1, "Score: %d", points);
  mvprintw(2, WIDTH + 1, "Level: %d", level);
  mvprintw(3, WIDTH + 1, "Speed: %d", speed);
  mvprintw(4, WIDTH + 1, "Hi_score: %d", highScore);
}