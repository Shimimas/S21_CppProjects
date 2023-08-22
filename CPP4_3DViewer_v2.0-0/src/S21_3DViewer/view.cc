#include "view.h"

#include <iostream>

namespace s21 {

View::View(QWidget* parent) : QOpenGLWidget(parent) {
  setGeometry(220, 10, 800, 600);
}

void View::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_STIPPLE);
}

void View::resizeGL(int width, int height) { glViewport(0, 0, width, height); }

void View::paintGL() {
  glClearColor(settings_[SETTING_MAIN_COLOR_FIRST] / 255.0,
               settings_[SETTING_MAIN_COLOR_SECOND] / 255.0,
               settings_[SETTING_MAIN_COLOR_THIRD] / 255.0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -2);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  draw();
}

void View::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void View::mouseMoveEvent(QMouseEvent* mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void View::draw() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (settings_[SETTING_MAIN_TYPE] == 1) {
    glFrustum(-1, 1, -1, 1, 1, 10);
  } else {
    glOrtho(-1, 1, -1, 1, 1, 10);
  }
  glVertexPointer(3, GL_FLOAT, 0, vertex_array_);
  glEnableClientState(GL_VERTEX_ARRAY);

  glLineWidth(settings_[SETTING_LINE_SIZE]);
  glLineStipple(1, settings_[SETTING_LINE_TYPE]);
  if (settings_[SETTING_VERTEX_TYPE] != 0) {
    glPointSize(settings_[SETTING_VERTEX_SIZE]);
    glColor3f(settings_[SETTING_VERTEX_COLOR_FIRST],
              settings_[SETTING_VERTEX_COLOR_SECOND],
              settings_[SETTING_VERTEX_COLOR_THIRD]);
    switch (settings_[SETTING_VERTEX_TYPE]) {
      case 1:
        glDisable(GL_POINT_SMOOTH);
        glDrawElements(GL_POINTS, polygons_count_, GL_UNSIGNED_INT,
                       polygons_array_);
        break;
      case 2:
        glEnable(GL_POINT_SMOOTH);
        glDrawElements(GL_POINTS, polygons_count_, GL_UNSIGNED_INT,
                       polygons_array_);
        break;
      default:
        break;
    }
  }
  glColor3f(settings_[SETTING_LINE_COLOR_FIRST],
            settings_[SETTING_LINE_COLOR_SECOND],
            settings_[SETTING_LINE_COLOR_THIRD]);
  glDrawElements(GL_LINES, polygons_count_, GL_UNSIGNED_INT, polygons_array_);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void View::set_start_settings(const int* settings_from_facade) {
  for (int i = 0; i < 14; i++) {
    settings_[i] = settings_from_facade[i];
  }
  delete[] settings_from_facade;
  update();
}

void View::set_model(float* vertex_array, unsigned int* polygons_array,
                     int polygons_amount) {
  vertex_array_ = vertex_array;
  polygons_array_ = polygons_array;
  polygons_count_ = polygons_amount;
}

void View::setAxisRotate(char axis_rotate) { axis_rotate_ = axis_rotate; }

void View::setAxisMove(char axis_move) { axis_move_ = axis_move; }

int View::getOldScale() { return old_scale_; }

int View::getOldRotate() { return old_rotate_; }

int View::getOldMove() { return old_move_; }

void View::setOldScale(int old_scale) { old_scale_ = old_scale; }

void View::setOldRotate(int old_rotate) { old_rotate_ = old_rotate; }

void View::setOldMove(int old_move) { old_move_ = old_move; }

char View::getAxisRotate() { return axis_rotate_; }

char View::getAxisMove() { return axis_move_; }

void View::setLineSize(int new_line_size) {
  settings_[SETTING_LINE_SIZE] = new_line_size;
}

void View::setVertexSize(int new_vertex_size) {
  settings_[SETTING_VERTEX_SIZE] = new_vertex_size;
}

void View::setLineType(int new_line_type) {
  settings_[SETTING_LINE_TYPE] = new_line_type;
}

void View::setVertexType(int new_vertex_type) {
  settings_[SETTING_VERTEX_TYPE] = new_vertex_type;
}

void View::setMainType(int new_main_type) {
  settings_[SETTING_MAIN_TYPE] = new_main_type;
}

void View::setLineFirstColor(int first_color) {
  settings_[SETTING_LINE_COLOR_FIRST] = first_color;
}

void View::setLineSecondColor(int second_color) {
  settings_[SETTING_LINE_COLOR_SECOND] = second_color;
}

void View::setLineThirdColor(int third_color) {
  settings_[SETTING_LINE_COLOR_THIRD] = third_color;
}

void View::setVertexFirstColor(int first_color) {
  settings_[SETTING_VERTEX_COLOR_FIRST] = first_color;
}

void View::setVertexSecondColor(int second_color) {
  settings_[SETTING_VERTEX_COLOR_SECOND] = second_color;
}

void View::setVertexThirdColor(int third_color) {
  settings_[SETTING_VERTEX_COLOR_THIRD] = third_color;
}

void View::setMainFirstColor(int first_color) {
  settings_[SETTING_MAIN_COLOR_FIRST] = first_color;
}

void View::setMainSecondColor(int second_color) {
  settings_[SETTING_MAIN_COLOR_SECOND] = second_color;
}

void View::setMainThirdColor(int third_color) {
  settings_[SETTING_MAIN_COLOR_THIRD] = third_color;
}

}  // namespace s21
