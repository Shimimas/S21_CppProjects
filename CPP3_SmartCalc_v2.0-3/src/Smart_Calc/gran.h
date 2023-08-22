#ifndef GRAN_H
#define GRAN_H

#include <QWidget>

namespace Ui {
class Gran;
}

namespace s21 {

class Gran : public QWidget {
  Q_OBJECT

 public:
  explicit Gran(QWidget *parent = nullptr);
  ~Gran();

  double x_start = -10, y_start = -10, x_end = 10, y_end = 10;

 private:
  Ui::Gran *ui;

 private slots:
  void set_result();

 public slots:
  void slot_gran();
};

}  // namespace s21

#endif  // GRAN_H
