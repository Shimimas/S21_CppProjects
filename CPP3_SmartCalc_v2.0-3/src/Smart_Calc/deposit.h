#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDateEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

#include "s21_controller.h"

namespace Ui {
class Deposit;
}

namespace s21 {

class Deposit : public QWidget {
  Q_OBJECT

 public:
  explicit Deposit(QWidget* parent = nullptr, Controller* control = nullptr);
  ~Deposit();

 private:
  Ui::Deposit* ui;
  Controller* controller;

  const int sdvig = 31;

  int count_get = 0;
  int count_add = 0;

  QLabel* add_data_label[15];
  QLabel* get_data_label[15];
  QLabel* add_sum_label[15];
  QLabel* get_sum_label[15];
  QDateEdit* add_data_edit[15];
  QDateEdit* get_data_edit[15];
  QLineEdit* add_sum_edit[15];
  QLineEdit* get_sum_edit[15];

  void create_add_data_label();
  void create_add_data_edit();
  void create_add_sum_label();
  void create_add_sum_edit();
  void create_get_data_label();
  void create_get_data_edit();
  void create_get_sum_label();
  void create_get_sum_edit();
  void delete_last_add();
  void delete_last_get();
  void get_move(const int& i, const int& move);
  void get_button_move(const int& move);
  void res_move(const int& move);
  std::string qstring_to_string(QString str);
  int get_payment_period();
  std::vector<std::pair<std::string, std::string>> create_get_vector();
  std::vector<std::pair<std::string, std::string>> create_add_vector();
  std::vector<std::string> create_string_input_vector();

 private slots:
  void create_add_list();
  void create_get_list();
  void delete_last_add_ell();
  void delete_last_get_ell();
  void calculation_result();

  void closeEvent(QCloseEvent* event);

 public slots:
  void slot_deposit();
};

}  // namespace s21

#endif  // DEPOSIT_H
