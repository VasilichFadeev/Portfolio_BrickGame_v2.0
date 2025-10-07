#include <QApplication>

#include "tetris_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  TetrisWindow window;
  window.show();
  return app.exec();
}