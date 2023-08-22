#include "x.h"

#include "ui_x.h"

namespace s21 {

X::X(QWidget *parent) : QWidget(parent), ui(new Ui::X) {
  ui->setupUi(this);

  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(set_result()));
}

X::~X() { delete ui; }

void X::set_result() {
  x = ui->lineEdit->text().toDouble();
  hide();
}

void X::slot_x(){};

}  // namespace s21
