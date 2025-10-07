#include <QApplication>

#include "tetris_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::TetrisWindow window;
  window.show();
  return app.exec();
}