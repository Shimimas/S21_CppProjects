#include "mainwindow.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), facade_(new s21_facade(this)) {
  facade_->create_start_settings();

  connect(facade_->getPushButton(OPEN_BUTTON), SIGNAL(clicked()), this,
          SLOT(createFilePath()));

  connect(facade_->getPushButton(X_MOVING_BUTTON), SIGNAL(clicked()), this,
          SLOT(setXAxisMove()));
  connect(facade_->getPushButton(Y_MOVING_BUTTON), SIGNAL(clicked()), this,
          SLOT(setYAxisMove()));
  connect(facade_->getPushButton(Z_MOVING_BUTTON), SIGNAL(clicked()), this,
          SLOT(setYAxisMove()));
  connect(facade_->getPushButton(X_ROTATE_BUTTON), SIGNAL(clicked()), this,
          SLOT(setXAxisRotate()));
  connect(facade_->getPushButton(Y_ROTATE_BUTTON), SIGNAL(clicked()), this,
          SLOT(setYAxisRotate()));
  connect(facade_->getPushButton(Z_ROTATE_BUTTON), SIGNAL(clicked()), this,
          SLOT(setZAxisRotate()));

  connect(facade_->getSlider(SCALE), SIGNAL(valueChanged(int)), this,
          SLOT(changeScale(int)));
  connect(facade_->getSlider(ROTATE), SIGNAL(valueChanged(int)), this,
          SLOT(changeRotate(int)));
  connect(facade_->getSlider(SHIFT), SIGNAL(valueChanged(int)), this,
          SLOT(changeMove(int)));

  connect(facade_->getSlider(LINE_SIZE), SIGNAL(valueChanged(int)), this,
          SLOT(changeLineSize(int)));
  connect(facade_->getSlider(VERTEX_SIZE), SIGNAL(valueChanged(int)), this,
          SLOT(changeVertexSize(int)));

  connect(facade_->getComBox(LINE_TYPE),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeLineType(const QString)));
  connect(facade_->getComBox(VERTEX_TYPE),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeVertexType(const QString)));
  connect(facade_->getComBox(MAIN_TYPE),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeMainType(const QString)));

  connect(facade_->getComBox(LINE_COLOR),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeLineColor(const QString)));
  connect(facade_->getComBox(MAIN_COLOR),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeMainColor(const QString)));
  connect(facade_->getComBox(VERTEX_COLOR),
          SIGNAL(currentTextChanged(const QString)), this,
          SLOT(changeVertexColor(const QString)));

  connect(facade_->getPushButton(SCREENSHOT_BUTTON), SIGNAL(clicked()), this,
          SLOT(screenshot()));
  connect(facade_->getPushButton(GIF_BUTTON), SIGNAL(clicked()), this,
          SLOT(gif()));
}

void MainWindow::createFilePath() { facade_->createFilePath(); }

void MainWindow::setXAxisRotate() { facade_->setXAxisRotate(); }

void MainWindow::setYAxisRotate() { facade_->setYAxisRotate(); }

void MainWindow::setZAxisRotate() { facade_->setZAxisRotate(); }

void MainWindow::setXAxisMove() { facade_->setXAxisMove(); }

void MainWindow::setYAxisMove() { facade_->setYAxisMove(); }

void MainWindow::setZAxisMove() { facade_->setZAxisMove(); }

void MainWindow::changeScale(int new_scale) { facade_->changeScale(new_scale); }

void MainWindow::changeRotate(int new_rotate) {
  facade_->changeRotate(new_rotate);
}

void MainWindow::changeMove(int new_move) { facade_->changeMove(new_move); }

void MainWindow::changeLineSize(int new_line_size) {
  facade_->changeLineSize(new_line_size);
}

void MainWindow::changeVertexSize(int new_vertex_size) {
  facade_->changeVertexSize(new_vertex_size);
}

void MainWindow::changeLineType(const QString text) {
  facade_->changeLineType(text);
}

void MainWindow::changeVertexType(const QString text) {
  facade_->changeVertexType(text);
}

void MainWindow::changeMainType(const QString text) {
  facade_->changeMainType(text);
}

void MainWindow::changeLineColor(const QString text) {
  facade_->changeLineColor(text);
}

void MainWindow::changeVertexColor(const QString text) {
  facade_->changeVertexColor(text);
}

void MainWindow::changeMainColor(const QString text) {
  facade_->changeMainColor(text);
}

void MainWindow::createGif() {
  GIF_->addFrame(facade_->getView()->grabFramebuffer().scaled(640, 480));
  if (GIF_->frameCount() == 50) {
    timer_->stop();
    QFileDialog Img(this);
    QString curDir =
        Img.getSaveFileName(this, tr("Save a Gif"), "GIF", tr("image (*.gif)"));
    GIF_->save(curDir + QDate::currentDate().toString() + " " +
               QTime::currentTime().toString() + ".gif");
    delete GIF_;
    delete timer_;
  }
}

void MainWindow::gif() {
  GIF_ = new QGifImage();
  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()), this, SLOT(createGif()));
  timer_->start(100);
}

void MainWindow::screenshot() {
  QScreen *screen_primary = QGuiApplication::primaryScreen();
  QPixmap screen = screen_primary->grabWindow(this->winId(), 220, 10, 800, 600);
  QString fileName = QFileDialog::getSaveFileName(
      0, "Сохранить как...", QDir::currentPath(),
      "All types(*.*);;PNG (*.png);;JPG (*jpeg *jpg);; BMP (*.bmp)");
  if (!fileName.isNull()) {
    screen.save(fileName, 0, 100);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton exit_question = QMessageBox::question(
      this, QApplication::applicationName(),
      tr("Do you want to close programm?"), QMessageBox::Yes | QMessageBox::No,
      QMessageBox::No);
  if (exit_question == QMessageBox::No) {
    event->ignore();
  } else {
    facade_->getPaint()->setSettingsInFile();
  }
}

}  // namespace s21
