#include <QApplication>

#include "../controller/s21_controller.h"
#include "mainwindow.h"
#include "s21_facade.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w(nullptr);
  w.show();
  return a.exec();
}
