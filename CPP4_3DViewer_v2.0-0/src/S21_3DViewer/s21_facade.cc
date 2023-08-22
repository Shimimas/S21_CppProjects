#include "s21_facade.h"

namespace s21 {

s21_facade::s21_facade(QWidget *parent)
    : control_(Controller::ControllerInstance()),
      paint_(new Painting(parent)),
      view_(new View(parent)) {}

void s21_facade::create_start_settings() {
  view_->set_start_settings(paint_->getStartingSettings());
}

QPushButton *s21_facade::getPushButton(int i) { return paint_->getButton(i); }

QSlider *s21_facade::getSlider(int i) { return paint_->getSlider(i); }

QComboBox *s21_facade::getComBox(int i) { return paint_->getComBox(i); }

void s21_facade::createFilePath() {
  control_.ClearModel();
  control_.Parsing(paint_->createFilePath());
  view_->set_model(control_.GetVertexArray(), control_.GetPolygonArray(),
                   control_.GetPolygonsAmount());
  view_->update();
}

void s21_facade::setXAxisRotate() { view_->setAxisRotate('x'); }

void s21_facade::setYAxisRotate() { view_->setAxisRotate('y'); }

void s21_facade::setZAxisRotate() { view_->setAxisRotate('z'); }

void s21_facade::setXAxisMove() { view_->setAxisMove('x'); }

void s21_facade::setYAxisMove() { view_->setAxisMove('y'); }

void s21_facade::setZAxisMove() { view_->setAxisMove('z'); }

void s21_facade::changeScale(int new_scale) {
  view_->getOldScale() > new_scale
      ? control_.Scale(pow(0.9, (view_->getOldScale() - new_scale)))
      : control_.Scale(pow((10.0 / 9.0), (new_scale - view_->getOldScale())));
  view_->setOldScale(new_scale);
  view_->set_model(control_.GetVertexArray(), control_.GetPolygonArray(),
                   control_.GetPolygonsAmount());
  view_->update();
}

void s21_facade::changeRotate(int new_rotate) {
  view_->getOldRotate() > new_rotate
      ? control_.TurnAround(10 * (view_->getOldRotate() - new_rotate),
                            view_->getAxisRotate())
      : control_.TurnAround(-10 * (new_rotate - view_->getOldRotate()),
                            view_->getAxisRotate());
  view_->setOldRotate(new_rotate);
  view_->set_model(control_.GetVertexArray(), control_.GetPolygonArray(),
                   control_.GetPolygonsAmount());
  view_->update();
}

void s21_facade::changeMove(int new_move) {
  view_->getOldMove() > new_move
      ? control_.Shift(-0.1 * (view_->getOldMove() - new_move),
                       view_->getAxisMove())
      : control_.Shift(0.1 * (new_move - view_->getOldMove()),
                       view_->getAxisMove());
  view_->setOldMove(new_move);
  view_->set_model(control_.GetVertexArray(), control_.GetPolygonArray(),
                   control_.GetPolygonsAmount());
  view_->update();
}

void s21_facade::changeLineSize(int new_line_size) {
  view_->setLineSize(new_line_size);
  view_->update();
}

void s21_facade::changeVertexSize(int new_vertex_size) {
  view_->setVertexSize(new_vertex_size);
  view_->update();
}

void s21_facade::changeLineType(const QString text) {
  view_->setLineType(paint_->changeLineType(text));
  view_->update();
}

void s21_facade::changeVertexType(const QString text) {
  view_->setVertexType(paint_->changeVertexType(text));
  view_->update();
}

void s21_facade::changeMainType(const QString text) {
  view_->setMainType(paint_->changeMainType(text));
  view_->update();
}

void s21_facade::changeLineColor(const QString text) {
  int first_color, second_color, third_color;
  paint_->findAndSetColor(text, first_color, second_color, third_color);
  view_->setLineFirstColor(first_color);
  view_->setLineSecondColor(second_color);
  view_->setLineThirdColor(third_color);
  view_->update();
}

void s21_facade::changeVertexColor(const QString text) {
  int first_color, second_color, third_color;
  paint_->findAndSetColor(text, first_color, second_color, third_color);
  view_->setVertexFirstColor(first_color);
  view_->setVertexSecondColor(second_color);
  view_->setVertexThirdColor(third_color);
  view_->update();
}

void s21_facade::changeMainColor(const QString text) {
  int first_color, second_color, third_color;
  paint_->findAndSetColor(text, first_color, second_color, third_color);
  view_->setMainFirstColor(first_color);
  view_->setMainSecondColor(second_color);
  view_->setMainThirdColor(third_color);
  view_->update();
}

View *s21_facade::getView() { return view_; }

Painting *s21_facade::getPaint() { return paint_; }

}  // namespace s21
