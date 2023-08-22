#include "credit_calc.h"

#include "ui_credit_calc.h"

namespace s21 {

Credit_calc::Credit_calc(QWidget *parent, Controller *control)
    : QWidget(parent), ui(new Ui::Credit_calc), controller(control) {
  ui->setupUi(this);

  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(credit_calculation()));
}

Credit_calc::~Credit_calc() { delete ui; }

void Credit_calc::credit_calculation() {
  QByteArray sum_bit = ui->lineEdit_sum->text().toLocal8Bit();
  std::string sum = sum_bit.data();
  QByteArray time_bit = ui->lineEdit_time->text().toLocal8Bit();
  std::string time = time_bit.data();
  QByteArray percent_bit = ui->lineEdit_percent->text().toLocal8Bit();
  std::string percent = percent_bit.data();
  bool type = false;
  if (ui->radioButton_dif->isChecked()) {
    type = true;
  }
  std::pair<const std::vector<double>, const bool> result =
      controller->credit(sum, percent, time, type);
  if (result.second) {
    QString string_monthly_payment = QString::number(result.first[0]);
    QString string_term = QString::number(result.first[1]);
    QString string_total_payment = QString::number(result.first[2]);
    ui->label_9->setText(string_monthly_payment);
    ui->label_10->setText(string_term);
    ui->label_11->setText(string_total_payment);
  } else {
    ui->label_9->setText("Incorrect input!");
    ui->label_10->setText("Incorrect input!");
    ui->label_11->setText("Incorrect input!");
  }
}

void Credit_calc::slot_credit_calc() {
  ui->lineEdit_sum->setText("0");
  ui->lineEdit_time->setText("0");
  ui->lineEdit_percent->setText("0");
  ui->label_9->setText("0");
  ui->label_10->setText("0");
  ui->label_11->setText("0");
}

}  // namespace s21
