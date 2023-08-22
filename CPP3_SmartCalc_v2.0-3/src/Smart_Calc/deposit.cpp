#include "deposit.h"

#include "ui_deposit.h"

namespace s21 {

Deposit::Deposit(QWidget* parent, Controller* control)
    : QWidget(parent), ui(new Ui::Deposit), controller(control) {
  ui->setupUi(this);

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(create_add_list()));
  connect(ui->pushButton_get, SIGNAL(clicked()), this, SLOT(create_get_list()));
  connect(ui->pushButton_clear_add, SIGNAL(clicked()), this,
          SLOT(delete_last_add_ell()));
  connect(ui->pushButton_clear_get, SIGNAL(clicked()), this,
          SLOT(delete_last_get_ell()));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(calculation_result()));
}

Deposit::~Deposit() { delete ui; }

void Deposit::create_add_data_label() {
  add_data_label[count_add] = new QLabel(this);
  add_data_label[count_add]->resize(60, 31);
  add_data_label[count_add]->setStyleSheet(
      "QLabel {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  add_data_label[count_add]->move(10, ui->pushButton_clear_get->y() - 36);
  add_data_label[count_add]->setText("Дата");
  add_data_label[count_add]->show();
}

void Deposit::create_add_data_edit() {
  add_data_edit[count_add] = new QDateEdit(this);
  add_data_edit[count_add]->resize(125, 31);
  add_data_edit[count_add]->setStyleSheet(
      "QDateEdit {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  add_data_edit[count_add]->move(70, ui->pushButton_clear_get->y() - 36);
  add_data_edit[count_add]->show();
}

void Deposit::create_add_sum_label() {
  add_sum_label[count_add] = new QLabel(this);
  add_sum_label[count_add]->resize(75, 31);
  add_sum_label[count_add]->setStyleSheet(
      "QLabel {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  add_sum_label[count_add]->move(195, ui->pushButton_clear_get->y() - 36);
  add_sum_label[count_add]->setText("Сумма");
  add_sum_label[count_add]->show();
}

void Deposit::create_add_sum_edit() {
  add_sum_edit[count_add] = new QLineEdit(this);
  add_sum_edit[count_add]->resize(79, 31);
  add_sum_edit[count_add]->setStyleSheet(
      "QLineEdit {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px; qproperty-alignment: "
      "AlignRight;}");
  add_sum_edit[count_add]->move(270, ui->pushButton_clear_get->y() - 36);
  add_sum_edit[count_add]->setText("0");
  add_sum_edit[count_add]->show();
}

void Deposit::create_get_data_label() {
  get_data_label[count_get] = new QLabel(this);
  get_data_label[count_get]->resize(60, 31);
  get_data_label[count_get]->setStyleSheet(
      "QLabel {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  get_data_label[count_get]->move(10, ui->pushButton->y() - 7);
  get_data_label[count_get]->setText("Дата");
  get_data_label[count_get]->show();
}

void Deposit::create_get_data_edit() {
  get_data_edit[count_get] = new QDateEdit(this);
  get_data_edit[count_get]->resize(125, 31);
  get_data_edit[count_get]->setStyleSheet(
      "QDateEdit {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  get_data_edit[count_get]->move(70, ui->pushButton->y() - 7);
  get_data_edit[count_get]->show();
}

void Deposit::create_get_sum_label() {
  get_sum_label[count_get] = new QLabel(this);
  get_sum_label[count_get]->resize(75, 31);
  get_sum_label[count_get]->setStyleSheet(
      "QLabel {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px;}");
  get_sum_label[count_get]->move(195, ui->pushButton->y() - 7);
  get_sum_label[count_get]->setText("Сумма");
  get_sum_label[count_get]->show();
}

void Deposit::create_get_sum_edit() {
  get_sum_edit[count_get] = new QLineEdit(this);
  get_sum_edit[count_get]->resize(79, 31);
  get_sum_edit[count_get]->setStyleSheet(
      "QLineEdit {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); "
      "border: 3px solid gray; font-size: 20px; qproperty-alignment: "
      "AlignRight;}");
  get_sum_edit[count_get]->move(270, ui->pushButton->y() - 7);
  get_sum_edit[count_get]->setText("0");
  get_sum_edit[count_get]->show();
}

void Deposit::create_add_list() {
  if (count_add < 15) {
    this->resize(this->width(), this->height() + sdvig);
    get_button_move(sdvig);
    create_add_data_label();
    create_add_data_edit();
    create_add_sum_label();
    create_add_sum_edit();
    count_add++;
    for (int i = 0; i < count_get; i++) {
      get_move(i, sdvig);
    }
    res_move(sdvig);
  }
}

void Deposit::create_get_list() {
  if (count_get < 15) {
    this->resize(this->width(), this->height() + sdvig);
    create_get_data_label();
    create_get_data_edit();
    create_get_sum_label();
    create_get_sum_edit();
    res_move(sdvig);
    count_get++;
  }
}

void Deposit::delete_last_add_ell() {
  if (count_add > 0) {
    delete_last_add();
    get_button_move(-sdvig);
    for (int i = 0; i < count_get; i++) {
      get_move(i, -sdvig);
    }
    this->resize(this->width(), this->height() - sdvig);
    res_move(-sdvig);
  }
}

void Deposit::delete_last_get_ell() {
  if (count_get > 0) {
    delete_last_get();
    this->resize(this->width(), this->height() - sdvig);
    res_move(-sdvig);
  }
}

void Deposit::delete_last_add() {
  delete add_data_label[count_add - 1];
  delete add_sum_label[count_add - 1];
  delete add_data_edit[count_add - 1];
  delete add_sum_edit[count_add - 1];
  count_add--;
}

void Deposit::delete_last_get() {
  delete get_data_label[count_get - 1];
  delete get_sum_label[count_get - 1];
  delete get_data_edit[count_get - 1];
  delete get_sum_edit[count_get - 1];
  count_get--;
}

void Deposit::get_move(const int& i, const int& move) {
  get_data_label[i]->move(10, get_data_label[i]->y() + move);
  get_sum_label[i]->move(195, get_sum_label[i]->y() + move);
  get_data_edit[i]->move(70, get_data_edit[i]->y() + move);
  get_sum_edit[i]->move(270, get_sum_edit[i]->y() + move);
}

void Deposit::res_move(const int& move) {
  ui->pushButton->move(10, ui->pushButton->y() + move);
  ui->label_7->move(10, ui->label_7->y() + move);
  ui->label_8->move(10, ui->label_8->y() + move);
  ui->label_9->move(10, ui->label_9->y() + move);
  ui->label_10->move(10, ui->label_10->y() + move);
  ui->label_11->move(250, ui->label_11->y() + move);
  ui->label_12->move(250, ui->label_12->y() + move);
  ui->label_13->move(250, ui->label_13->y() + move);
}

void Deposit::get_button_move(const int& move) {
  ui->pushButton_get->move(ui->pushButton_get->x(),
                           ui->pushButton_get->y() + move);
  ui->pushButton_clear_get->move(ui->pushButton_clear_get->x(),
                                 ui->pushButton_clear_get->y() + move);
}

void Deposit::slot_deposit() {
  ui->lineEdit->setText("0");
  ui->lineEdit_2->setText("0");
  ui->lineEdit_3->setText("0");
  ui->lineEdit_4->setText("0");
  ui->label_11->setText("0");
  ui->label_12->setText("0");
  ui->label_13->setText("0");
}

void Deposit::closeEvent(QCloseEvent* event) {
  int count_tmp = count_get;
  for (int i = 0; i < count_tmp; i++) {
    delete_last_get_ell();
  }
  count_tmp = count_add;
  for (int i = 0; i < count_tmp; i++) {
    delete_last_add_ell();
  }
  event->accept();
}

std::string Deposit::qstring_to_string(QString str) {
  QByteArray str_byte = str.toLocal8Bit();
  std::string result = str_byte.data();
  return result;
}

int Deposit::get_payment_period() {
  int result = 0;
  if (ui->radioButton->isChecked()) {
    result = 2;
  } else if (ui->radioButton_3->isChecked()) {
    result = 1;
  } else if (ui->radioButton_4->isChecked()) {
    result = 3;
  }
  return result;
}

std::vector<std::pair<std::string, std::string>> Deposit::create_add_vector() {
  std::vector<std::pair<std::string, std::string>> add_list;
  for (int i = 0; i < count_add; i++) {
    add_list.push_back({qstring_to_string(add_data_edit[i]->text()),
                        qstring_to_string(add_sum_edit[i]->text())});
  }
  return add_list;
}

std::vector<std::pair<std::string, std::string>> Deposit::create_get_vector() {
  std::vector<std::pair<std::string, std::string>> get_list;
  for (int i = 0; i < count_get; i++) {
    get_list.push_back({qstring_to_string(get_data_edit[i]->text()),
                        qstring_to_string(get_sum_edit[i]->text())});
  }
  return get_list;
}

std::vector<std::string> Deposit::create_string_input_vector() {
  std::vector<std::string> result;
  result.push_back(qstring_to_string(ui->lineEdit->text()));
  result.push_back(qstring_to_string(ui->lineEdit_2->text()));
  result.push_back(qstring_to_string(ui->lineEdit_3->text()));
  result.push_back(qstring_to_string(ui->lineEdit_4->text()));
  return result;
}

void Deposit::calculation_result() {
  const std::vector<std::string> input_vector = create_string_input_vector();
  const bool interest_capitalization = ui->checkBox->checkState();
  const int payment_period = get_payment_period();
  const std::pair<std::vector<std::pair<std::string, std::string>>,
                  std::vector<std::pair<std::string, std::string>>>
      add_and_get_lists = {create_add_vector(), create_get_vector()};
  const std::pair<std::vector<double>, bool> result = controller->deposit(
      input_vector, interest_capitalization, payment_period, add_and_get_lists);
  if (result.second) {
    QString string_interest_charges = QString::number(result.first[0]);
    QString string_nalog = QString::number(result.first[1]);
    QString string_deposit_sum = QString::number(result.first[2]);
    ui->label_11->setText(string_interest_charges);
    ui->label_12->setText(string_nalog);
    ui->label_13->setText(string_deposit_sum);
  } else {
    ui->label_11->setText("Incorrect input!");
    ui->label_12->setText("Incorrect input!");
    ui->label_13->setText("Incorrect input!");
  }
}

}  // namespace s21
