/**
 * @file generateApple.cpp
 * @brief Реализация функции SnakeGame::generateApple.
 */
#include "../../brick_game/snake/snake/snake_terminal.h"

namespace s21 {
/**
 * @brief Генерирует новое яблоко на игровом поле.
 *
 * Случайным образом выбирает свободную клетку внутри рамки
 * и размещает в ней символ яблока (`●`).
 */
void SnakeGame::generateApple() {
  srand(time(0));
  int y, x;
  do {
    y = rand() % (HEIGHT - 2) + 1;
    x = rand() % (WIDTH - 2) + 1;
  } while (field[y][x] != L' ');
  field[y][x] = L'●';
}
}