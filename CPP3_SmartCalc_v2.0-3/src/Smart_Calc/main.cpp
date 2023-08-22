#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  s21::Model model;
  s21::Controller controller(&model);
  QApplication a(argc, argv);
  s21::MainWindow w(nullptr, &controller);
  w.show();
  return a.exec();
}
