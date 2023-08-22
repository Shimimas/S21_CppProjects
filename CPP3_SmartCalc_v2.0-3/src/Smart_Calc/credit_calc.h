#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QWidget>

#include "s21_controller.h"

namespace Ui {
class Credit_calc;
}

namespace s21 {

class Credit_calc : public QWidget {
  Q_OBJECT

 public:
  explicit Credit_calc(QWidget *parent = nullptr,
                       s21::Controller *control = nullptr);
  ~Credit_calc();

 private:
  Ui::Credit_calc *ui;
  Controller *controller;

 public slots:
  void credit_calculation();
  void slot_credit_calc();
};

}  // namespace s21

#endif  // CREDIT_CALC_H
