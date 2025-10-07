#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <QLabel>
#include <QTimer>
#include <QWidget>

#include "tetris_game.h"

namespace s21 {
/**
 * @brief Главное окно десктопного Тетриса
 */
class TetrisWindow : public QWidget {
 public:
  /** @brief Конструктор окна
   *  @param parent Родительский виджет (по умолчанию nullptr)
   */
  TetrisWindow(QWidget *parent = nullptr);

 protected:
  /** @brief Обработка нажатия клавиш
   *  @param event Событие клавиатуры
   */
  void keyPressEvent(QKeyEvent *event) override;

 private:
  QLabel *label; /**< Виджет для отображения игрового поля */
  QTimer *timer; /**< Таймер для автоматического падения фигур */
  TetrisGame game; /**< Игровой объект */
};
}  // namespace s21

#endif  // TETRIS_WINDOW_H