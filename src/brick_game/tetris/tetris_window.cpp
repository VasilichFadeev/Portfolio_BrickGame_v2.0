#include "tetris_window.h"

#include <QFont>
#include <QKeyEvent>
#include <QVBoxLayout>

TetrisWindow::TetrisWindow(QWidget *parent) : QWidget(parent) {
  setWindowTitle("Tetris");
  resize(500, 600);
  QVBoxLayout *layout = new QVBoxLayout(this);
  label = new QLabel(this);
  label->setFont(QFont("Courier New", 12));
  label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->addWidget(label);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, [this]() {
    if (game.update()) {
      label->setText(game.render());
      timer->start(game.getSpeed());
    } else {
      label->setText(game.render());
      timer->stop();
    }
  });

  label->setText(game.render());
  timer->start(game.getSpeed());
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      game.userInput(Left);
      break;
    case Qt::Key_Right:
      game.userInput(Right);
      break;
    case Qt::Key_Down:
      game.userInput(Down);
      break;
    case Qt::Key_Up:
      game.userInput(Up);
      break;
    case Qt::Key_Space:
      game.userInput(Pause);
      if (!game.isPaused())
        timer->start(game.getSpeed());
      else
        timer->stop();
      break;
    case Qt::Key_Q:
      game.userInput(Terminate);
      break;
  }
  label->setText(game.render());
}