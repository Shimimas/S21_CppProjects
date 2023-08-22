#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent, s21::Controller *control)
    : QMainWindow(parent),
      controller(control),
      ui(new Ui::MainWindow),
      graph(new Graph(nullptr, control)),
      credit_calc(new Credit_calc(nullptr, control)),
      deposit(new Deposit(nullptr, control)),
      gran(new Gran(nullptr)),
      x(new X(nullptr)) {
  ui->setupUi(this);

  connect(this, &MainWindow::signal_graph, graph, &Graph::slot_graph);
  connect(this, &MainWindow::signal_credit_calc, credit_calc,
          &Credit_calc::slot_credit_calc);
  connect(this, &MainWindow::signal_deposit, deposit, &Deposit::slot_deposit);
  connect(this, &MainWindow::signal_gran, gran, &Gran::slot_gran);
  connect(this, &MainWindow::signal_x, x, &X::slot_x);

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(create_input_string()));
  connect(ui->pushButton_expand, SIGNAL(toggled(bool)), this,
          SLOT(create_new_form(bool)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::backspace() {
  QString text = ui->res_show->text();
  text.chop(1);
  if (text.isEmpty()) {
    text = "";
  }
  ui->res_show->setText(text);
}

void MainWindow::set_result() {
  QString input = ui->res_show->text();
  QByteArray res_bit = input.toLocal8Bit();
  std::string res_str = res_bit.data();
  std::pair<double, bool> result = controller->input(res_str, x->x);
  if (result.second == false) {
    ui->res_show->setText("Incorrect input!");
  } else {
    QString string_res = QString::number(result.first);
    ui->res_show->setText(string_res);
  }
}

void MainWindow::create_input_string() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "AC") {
    ui->res_show->setText("");
  } else if (button->text() == "<-") {
    backspace();
  } else if (button->text() == "=") {
    set_result();
  } else if (ui->res_show->text().size() < 255) {
    ui->res_show->setText(ui->res_show->text() + button->text());
    if (button->text() == "cos" || button->text() == "sin" ||
        button->text() == "tan" || button->text() == "acos" ||
        button->text() == "asin" || button->text() == "atan" ||
        button->text() == "sqrt" || button->text() == "ln" ||
        button->text() == "log") {
      ui->res_show->setText(ui->res_show->text() + "(");
    }
  }
}

void MainWindow::extended_version() {
  ui->pushButton_0->setText("");
  ui->pushButton_1->setText("tan");
  ui->pushButton_2->setText("atan");
  ui->pushButton_3->setText("log");
  ui->pushButton_4->setText("sin");
  ui->pushButton_5->setText("asin");
  ui->pushButton_6->setText("ln");
  ui->pushButton_7->setText("cos");
  ui->pushButton_8->setText("acos");
  ui->pushButton_9->setText("sqrt");
  ui->pushButton_point->setText("");
  ui->pushButton_clear->setText("x");
  ui->pushButton_div->setText("");
  ui->pushButton_mod->setText("^");
  ui->pushButton_backspace->setText("e");
  ui->pushButton_mult->setText("(");
  ui->pushButton_plus->setText("");
  ui->pushButton_minus->setText(")");
  ui->pushButton_equal->setText("");
}

void MainWindow::regular_version() {
  ui->pushButton_0->setText("0");
  ui->pushButton_1->setText("1");
  ui->pushButton_2->setText("2");
  ui->pushButton_3->setText("3");
  ui->pushButton_4->setText("4");
  ui->pushButton_5->setText("5");
  ui->pushButton_6->setText("6");
  ui->pushButton_7->setText("7");
  ui->pushButton_8->setText("8");
  ui->pushButton_9->setText("9");
  ui->pushButton_point->setText(".");
  ui->pushButton_clear->setText("AC");
  ui->pushButton_div->setText("/");
  ui->pushButton_mod->setText("mod");
  ui->pushButton_backspace->setText("<-");
  ui->pushButton_mult->setText("*");
  ui->pushButton_plus->setText("+");
  ui->pushButton_minus->setText("-");
  ui->pushButton_equal->setText("=");
}

void MainWindow::create_new_form(bool state) {
  if (state) {
    extended_version();
  } else {
    regular_version();
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  emit signal_graph(ui->res_show->text(), gran->x_start, gran->x_end,
                    gran->y_start, gran->y_end);
  graph->show();
}

void MainWindow::on_pushButton_credit_calc_clicked() {
  emit signal_credit_calc();
  credit_calc->show();
}

void MainWindow::on_pushButton_deposit_calc_clicked() {
  emit signal_deposit();
  deposit->show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton exit_question = QMessageBox::question(
      this, QApplication::applicationName(),
      tr("Do you want to close programm?"), QMessageBox::Yes | QMessageBox::No,
      QMessageBox::No);
  if (exit_question == QMessageBox::No) {
    event->ignore();
  } else {
    graph->close();
    credit_calc->close();
    deposit->close();
  }
}

void MainWindow::on_pushButton_gran_clicked() {
  emit signal_gran();
  gran->show();
}

void MainWindow::on_pushButton_x_clicked() {
  emit signal_x();
  x->show();
}

}  // namespace s21
