#ifndef X_H
#define X_H

#include <QWidget>

namespace Ui {
class X;
}

namespace s21 {

class X : public QWidget {
  Q_OBJECT

 public:
  explicit X(QWidget *parent = nullptr);
  ~X();

  double x = 0;

 private:
  Ui::X *ui;

 private slots:
  void set_result();

 public slots:
  void slot_x();
};

}  // namespace s21

#endif  // X_H
