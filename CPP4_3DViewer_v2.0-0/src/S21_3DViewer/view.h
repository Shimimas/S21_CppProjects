#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QMainWindow>
#include <QtOpenGL>

namespace s21 {

typedef enum {
  SETTING_VERTEX_TYPE = 0,
  SETTING_VERTEX_SIZE = 1,
  SETTING_VERTEX_COLOR_FIRST = 2,
  SETTING_VERTEX_COLOR_SECOND = 3,
  SETTING_VERTEX_COLOR_THIRD = 4,
  SETTING_LINE_TYPE = 5,
  SETTING_LINE_SIZE = 6,
  SETTING_LINE_COLOR_FIRST = 7,
  SETTING_LINE_COLOR_SECOND = 8,
  SETTING_LINE_COLOR_THIRD = 9,
  SETTING_MAIN_TYPE = 10,
  SETTING_MAIN_COLOR_FIRST = 11,
  SETTING_MAIN_COLOR_SECOND = 12,
  SETTING_MAIN_COLOR_THIRD = 13
} settings_t;

class View : public QOpenGLWidget {
  Q_OBJECT

 private:
  float xRot, yRot;
  QPoint mPos;

  float *vertex_array_;
  unsigned int *polygons_array_;
  int polygons_count_ = 0, old_scale_ = 25, old_rotate_ = 0, old_move_ = 0;

  char axis_rotate_ = 'x', axis_move_ = 'x';

  int settings_[14];

  void draw();

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

  void change_vertex_type(const QString &text);
  void change_line_type(const QString &text);
  void change_main_type(const QString &text);
  void change_vertex_size(int new_size);
  void change_line_size(int new_size);
  void find_and_set_color(const QString &text, int &first, int &second,
                          int &third);

 public:
  View(QWidget *parent = nullptr);

  int getOldScale();
  int getOldRotate();
  int getOldMove();

  void setOldScale(int old_scale);
  void setOldRotate(int old_rotate);
  void setOldMove(int old_move);

  char getAxisRotate();
  char getAxisMove();

  void setAxisRotate(char axis_rotate);
  void setAxisMove(char axis_move);

  void setLineSize(int new_line_size);
  void setVertexSize(int new_vertex_size);

  void setLineType(int new_line_type);
  void setVertexType(int new_vertex_type);
  void setMainType(int new_main_type);

  void setLineFirstColor(int first);
  void setLineSecondColor(int second);
  void setLineThirdColor(int third);

  void setVertexFirstColor(int first);
  void setVertexSecondColor(int second);
  void setVertexThirdColor(int third);

  void setMainFirstColor(int first);
  void setMainSecondColor(int second);
  void setMainThirdColor(int third);

  void set_start_settings(const int *settings_from_facade);
  void set_model(float *vertex_array, unsigned int *polygons_array,
                 int polygons_amount);
};

}  // namespace s21

#endif  // VIEW_H
