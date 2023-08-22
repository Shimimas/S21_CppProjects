#ifndef S21_FACADE_H
#define S21_FACADE_H

#include "../controller/s21_controller.h"
#include "painting.h"
#include "view.h"

namespace s21 {

class s21_facade {
 public:
  s21_facade(QWidget *parent);

  void create_start_settings();
  void createFilePath();

  QPushButton *getPushButton(int i);
  QSlider *getSlider(int i);
  QComboBox *getComBox(int i);

  void setXAxisRotate();
  void setYAxisRotate();
  void setZAxisRotate();
  void setXAxisMove();
  void setYAxisMove();
  void setZAxisMove();

  void changeScale(int new_scale);
  void changeRotate(int new_rotate);
  void changeMove(int new_move);

  void changeLineSize(int new_line_size);
  void changeVertexSize(int new_vertex_size);

  void changeLineType(const QString text);
  void changeVertexType(const QString text);
  void changeMainType(const QString text);

  void changeLineColor(const QString text);
  void changeVertexColor(const QString text);
  void changeMainColor(const QString text);

  View *getView();
  Painting *getPaint();

 private:
  Controller &control_;
  Painting *paint_;
  View *view_;
};

}  // namespace s21

#endif  // S21_FACADE_H
