#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QTimer>

#include "../controller/s21_controller.h"
#include "s21_facade.h"
#include "view.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);

 private:
  s21_facade *facade_;

  QGifImage *GIF_;
  QTimer *timer_;

  void closeEvent(QCloseEvent *event) override;

 public slots:
  void createFilePath();

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

  void gif();
  void createGif();
  void screenshot();
};

}  // namespace s21
#endif  // MAINWINDOW_H
