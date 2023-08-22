#include "graph.h"

#include "ui_graph.h"

namespace s21 {

Graph::Graph(QWidget *parent, s21::Controller *control)
    : QWidget(parent), ui(new Ui::Graph), controller(control) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::create_graphs(std::string res_string, double x_start,
                          double x_end) {
  QVector<double> x_tmp;
  QVector<double> y_tmp;
  double h = (fabs(x_start) + fabs(x_end)) / 5000;
  bool false_ind = true;
  for (double x = x_start; x <= x_end; x += h) {
    std::pair<double, bool> result = controller->input(res_string, x);
    if (result.second != false) {
      x_tmp.push_back(x);
      y_tmp.push_back(result.first);
      false_ind = true;
    }
    if ((result.second == false && false_ind == true) || x + h > x_end) {
      x_array.push_back(x_tmp);
      y_array.push_back(y_tmp);
      x_tmp.clear();
      y_tmp.clear();
      false_ind = false;
    }
  }
}

void Graph::slot_graph(QString res_str, double x_start, double x_end,
                       double y_start, double y_end) {
  ui->widget->clearGraphs();

  ui->label_2->setText("Function Graph " + res_str);

  ui->widget->xAxis->setRange(x_start, x_end);
  ui->widget->yAxis->setRange(y_start, y_end);

  QByteArray res_bit = res_str.toLocal8Bit();
  std::string res_string = res_bit.data();
  create_graphs(res_string, x_start, x_end);
  for (int i = 0; i < (int)x_array.size(); ++i) {
    ui->widget->addGraph();
    ui->widget->graph(i)->addData(x_array[i], y_array[i]);
  }
  ui->widget->replot();

  x_array.clear();
  y_array.clear();
}

}  // namespace s21
