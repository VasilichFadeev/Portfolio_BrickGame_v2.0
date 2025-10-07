#include "../../brick_game/tetris/brick_game.h"

/**
 * @brief Проверяет, хочет ли игрок выйти из игры.
 *
 * @param ch Код нажатой клавиши.
 * @return 1, если нажата клавиша выхода, 0 — иначе.
 */
int handleQuit(int ch) { return ch == 'q'; }