#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

#include "s21_controller.h"

namespace Ui {
class Graph;
}

namespace s21 {

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr, s21::Controller *control = nullptr);
  ~Graph();

 private:
  Ui::Graph *ui;
  Controller *controller;

  QVector<QVector<double>> x_array, y_array;

  void create_graphs(std::string res_string, double x_start, double x_end);

 public slots:
  void slot_graph(QString res_str, double x_start, double x_end, double y_start,
                  double y_end);
};

}  // namespace s21
#endif  // GRAPH_H
