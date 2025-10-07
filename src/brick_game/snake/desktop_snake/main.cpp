/**
 * @file main.cpp
 * @brief Точка входа в десктопную версию змейки.
 */
#include <QApplication>
#include <QFile>
#include <QFont>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <random>
#include <vector>

#include "desktop_snake.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::SnakeWindow window;
  window.show();
  return app.exec();
}