#include "gran.h"

#include "ui_gran.h"

namespace s21 {

Gran::Gran(QWidget *parent) : QWidget(parent), ui(new Ui::Gran) {
  ui->setupUi(this);

  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(set_result()));
}

Gran::~Gran() { delete ui; }

void Gran::set_result() {
  x_start = ui->lineEdit_x1->text().toDouble();
  x_end = ui->lineEdit_x2->text().toDouble();
  y_start = ui->lineEdit_y1->text().toDouble();
  y_end = ui->lineEdit_y2->text().toDouble();
  hide();
}

void Gran::slot_gran() {}

}  // namespace s21
