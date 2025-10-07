/**
 * @file inputHandler.cpp
 * @brief Реализация функции обработки ввода игрока.
 */ 
#include "../../brick_game/snake/snake/snake_terminal.h"

namespace s21 {
/**
 * @brief Обрабатывает ввод с клавиатуры.
 *
 * Поддерживает:
 * - стрелки для движения змеи,
 * - `SPACE` для паузы,
 * - `E` для активации турбо-режима,
 * - `Q` для выхода из игры.
 *
 * @param paused Ссылка на флаг паузы
 * @param running Ссылка на флаг работы игры
 */
void inputHandler(bool &paused, bool &running) {
  int ch = getch();
  if (ch != ERR) {
    switch (ch) {
      case KEY_LEFT:
        if (!paused) userInput(Left, false);
        break;
      case KEY_RIGHT:
        if (!paused) userInput(Right, false);
        break;
      case KEY_UP:
        if (!paused) userInput(Up, false);
        break;
      case KEY_DOWN:
        if (!paused) userInput(Down, false);
        break;
      case ' ':
        userInput(Pause, false);
        paused = !paused;
        break;
      case 'e':
      case 'E':
        if (!paused) userInput(Turbo, false);
        break;
      case 'q':
      case 'Q':
        running = false;
        break;
    }
  }
}
}