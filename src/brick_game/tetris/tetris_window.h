#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <QLabel>
#include <QTimer>
#include <QWidget>

#include "tetris_game.h"

class TetrisWindow : public QWidget {
 public:
  TetrisWindow(QWidget *parent = nullptr);

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private:
  QLabel *label;
  QTimer *timer;
  TetrisGame game;
};

#endif  // TETRIS_WINDOW_H