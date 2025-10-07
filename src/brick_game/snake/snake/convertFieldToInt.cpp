#include "snake_terminal.h"

namespace s21 {
/**
 * @brief Конвертирует символы игрового поля в числовое представление.
 *
 * Поле `field` хранится в виде символов (`█` — тело змеи, `●` — яблоко).
 * Эта функция преобразует его в числовое поле `fieldInt`:
 * - `1` — тело змеи
 * - `2` — яблоко
 * - `0` — пустая клетка
 */
void SnakeGame::convertFieldToInt() {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (field[y][x] == L'█') {
        fieldInt[y][x] = 1;
      } else if (field[y][x] == L'●') {
        fieldInt[y][x] = 2;
      } else {
        fieldInt[y][x] = 0;
      }
    }
  }
}
}  // namespace s21