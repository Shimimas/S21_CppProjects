#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QVector>
#include <string>

#include "credit_calc.h"
#include "deposit.h"
#include "gran.h"
#include "graph.h"
#include "s21_controller.h"
#include "x.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Controller *control = nullptr);
  ~MainWindow();

 private:
  s21::Controller *controller;
  Ui::MainWindow *ui;
  Graph *graph;
  Credit_calc *credit_calc;
  Deposit *deposit;
  Gran *gran;
  X *x;

  void backspace();
  void set_result();
  void extended_version();
  void regular_version();

 private slots:
  void create_input_string();
  void create_new_form(bool);

  void on_pushButton_graph_clicked();
  void on_pushButton_credit_calc_clicked();
  void on_pushButton_deposit_calc_clicked();

  void closeEvent(QCloseEvent *event);

  void on_pushButton_gran_clicked();

  void on_pushButton_x_clicked();

 signals:
  void signal_graph(QString res_str, double x_start, double x_end,
                    double y_start, double y_end);
  void signal_credit_calc();
  void signal_deposit();
  void signal_gran();
  void signal_x();
};

}  // namespace s21
#endif  // MAINWINDOW_H
