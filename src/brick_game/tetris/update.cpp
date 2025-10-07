#include "tetris_game.h"

/**
 * @brief Обновление состояния игры: падение фигуры, проверка линий
 * @return true если игра продолжается, false при окончании
 */
namespace s21 {
bool TetrisGame::update() {
  if (pause) return false;
  if (!isValid(currentPiece.shape, currentX, currentY + 1)) {
    placePiece();
    checkLines();
    spawnPiece();
    if (!isValid(currentPiece.shape, currentX, currentY)) {
      pause = true;
      saveHighScore();
      return false;
    }
  } else {
    currentY++;
  }
  return true;
}
}  // namespace s21