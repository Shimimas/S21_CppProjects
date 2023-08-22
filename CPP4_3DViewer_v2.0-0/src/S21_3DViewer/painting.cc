#include "painting.h"

namespace s21 {

Painting::Painting(QWidget *parent) : parent_(parent) {
  placeAndSettingAllElements();
}

const int *Painting::createIntSettingsArray(
    const std::vector<QString> result_string) {
  int *settings = new int[14];
  settings[0] = changeVertexType(result_string[0]);
  settings[1] = result_string[1].toInt();
  findAndSetColor(result_string[2], settings[2], settings[3], settings[4]);
  settings[5] = changeLineType(result_string[3]);
  settings[6] = result_string[4].toInt();
  findAndSetColor(result_string[5], settings[7], settings[8], settings[9]);
  settings[10] = changeMainType(result_string[6]);
  findAndSetColor(result_string[7], settings[11], settings[12], settings[13]);
  return settings;
}

void Painting::setStartWidgetsSettings(
    const std::vector<QString> result_string) {
  comboxes_[VERTEX_TYPE]->setCurrentIndex(
      comboxes_[VERTEX_TYPE]->findText(result_string[0]));
  sliders_[VERTEX_SIZE]->setValue(result_string[1].toInt());
  comboxes_[VERTEX_COLOR]->setCurrentIndex(
      comboxes_[VERTEX_COLOR]->findText(result_string[2]));
  comboxes_[LINE_TYPE]->setCurrentIndex(
      comboxes_[LINE_TYPE]->findText(result_string[3]));
  sliders_[LINE_SIZE]->setValue(result_string[4].toInt());
  comboxes_[LINE_COLOR]->setCurrentIndex(
      comboxes_[LINE_COLOR]->findText(result_string[5]));
  comboxes_[MAIN_TYPE]->setCurrentIndex(
      comboxes_[MAIN_TYPE]->findText(result_string[6]));
  comboxes_[MAIN_COLOR]->setCurrentIndex(
      comboxes_[MAIN_COLOR]->findText(result_string[7]));
}

const int *Painting::getStartingSettings() {
  std::ifstream file;
  std::vector<QString> result_string;
  file.open(
      (QDir::homePath() + "/CPP4_3DViewer_v2.0-0/src/S21_3DViewer/settings.cfg")
          .toLocal8Bit()
          .constData());
  if (!file) throw std::out_of_range("Do not such file or directory!");
  while (file) {
    std::string str;
    getline(file, str);
    QString qstr = QString::fromStdString(str);
    result_string.push_back(qstr);
  }
  file.close();
  setStartWidgetsSettings(result_string);
  return createIntSettingsArray(result_string);
}

void Painting::placeAndSettingAllElements() {
  placeAllElements();
  setLabelStyle();
  createComboxesText();
  settingSliders();
}

void Painting::settingCentralWidget() {
  parent_->setFixedSize(1240, 620);
  parent_->setStyleSheet("QWidget {background-color: rgb(235, 235, 235);}");
}

void Painting::placeAllElements() {
  settingCentralWidget();
  push_buttons_[OPEN_BUTTON] = createButton(10, 10, 200, 40, "OPEN");
  push_buttons_[SCREENSHOT_BUTTON] =
      createButton(10, 60, 200, 40, "SCREENSHOT");
  push_buttons_[GIF_BUTTON] = createButton(10, 110, 200, 40, "GIF");
  push_buttons_[X_MOVING_BUTTON] = createButton(1030, 130, 60, 40, "X");
  push_buttons_[Y_MOVING_BUTTON] = createButton(1100, 130, 60, 40, "Y");
  push_buttons_[Z_MOVING_BUTTON] = createButton(1170, 130, 60, 40, "Z");
  labels_[SCALING] = createLabel(1030, 10, 200, 40, "SCALING");
  labels_[MOVING] = createLabel(1030, 80, 200, 40, "MOVING");
  sliders_[SCALE] = createSlider(1030, 50, 200, 20);
  sliders_[SHIFT] = createSlider(1030, 180, 200, 20);
  labels_[ROTATION] = createLabel(1030, 210, 200, 40, "ROTATION");
  push_buttons_[X_ROTATE_BUTTON] = createButton(1030, 260, 60, 40, "X");
  push_buttons_[Y_ROTATE_BUTTON] = createButton(1100, 260, 60, 40, "Y");
  push_buttons_[Z_ROTATE_BUTTON] = createButton(1170, 260, 60, 40, "Z");
  sliders_[ROTATE] = createSlider(1030, 310, 200, 20);
  labels_[VERTICES_SETTINGS] =
      createLabel(10, 160, 200, 40, "VERTICES SETTINGS");
  labels_[VERTICES_SETTINGS_TYPE] = createLabel(10, 200, 100, 20, "TYPE");
  labels_[VERTICES_SETTINGS_SIZE] = createLabel(10, 230, 100, 20, "SIZE");
  labels_[VERTICES_SETTINGS_COLOR] = createLabel(10, 260, 100, 20, "COLOR");
  comboxes_[VERTEX_COLOR] = createCombox(110, 260, 100, 20);
  sliders_[VERTEX_SIZE] = createSlider(110, 230, 100, 20);
  comboxes_[VERTEX_TYPE] = createCombox(110, 200, 100, 20);
  labels_[EDGES_SETTINGS] = createLabel(10, 290, 200, 40, "EDGES SETTINGS");
  labels_[EDGES_SETTINGS_TYPE] = createLabel(10, 330, 100, 20, "TYPE");
  labels_[EDGES_SETTINGS_SIZE] = createLabel(10, 360, 100, 20, "SIZE");
  labels_[EDGES_SETTINGS_COLOR] = createLabel(10, 390, 100, 20, "COLOR");
  comboxes_[LINE_COLOR] = createCombox(110, 390, 100, 20);
  sliders_[LINE_SIZE] = createSlider(110, 360, 100, 20);
  comboxes_[LINE_TYPE] = createCombox(110, 330, 100, 20);
  labels_[MAIN_SETTINGS] = createLabel(10, 420, 200, 40, "MAIN SETTINGS");
  labels_[EDGES_SETTINGS_TYPE] = createLabel(10, 460, 100, 20, "PROJECTION");
  labels_[EDGES_SETTINGS_COLOR] = createLabel(10, 490, 100, 20, "COLOR");
  comboxes_[MAIN_TYPE] = createCombox(110, 460, 100, 20);
  comboxes_[MAIN_COLOR] = createCombox(110, 490, 100, 20);
  labels_[INFO] = createLabel(1030, 340, 200, 40, "INFO");
  labels_[INFO_VERTICES] = createLabel(1030, 380, 100, 20, "VERTICES");
  labels_[INFO_POLYGONS] = createLabel(1030, 410, 100, 20, "POLYGONS");
  labels_[INFO_PATH] = createLabel(1030, 440, 50, 20, "PATH");
  labels_[INFO_VERTICES_RESULT] = createLabel(1130, 380, 100, 20, "0");
  labels_[INFO_POLYGONS_RESULT] = createLabel(1130, 410, 100, 20, "0");
  labels_[INFO_PATH_RESULT] = createLabel(1080, 440, 150, 20, "0");
}

QPushButton *Painting::createButton(int x_move, int y_move, int x_resize,
                                    int y_resize, QString text) {
  QPushButton *button = new QPushButton(parent_);
  button->move(x_move, y_move);
  button->setStyleSheet(
      "QPushButton {background-color: rgb(215, 215, 215); color: rgb(0, 0, 0); "
      "border: 3px solid gray; border-radius: 5px; font-size: 20px;} "
      "QPushButton:pressed {background-color: rgb(211, 215, 207);}");
  button->resize(x_resize, y_resize);
  button->setText(text);
  return button;
}

QComboBox *Painting::createCombox(int x_move, int y_move, int x_resize,
                                  int y_resize) {
  QComboBox *combox = new QComboBox(parent_);
  combox->move(x_move, y_move);
  combox->setStyleSheet(
      "QComboBox {background-color: rgb(255, 255, 255); color: rgb(0, 0, 0);}");
  combox->resize(x_resize, y_resize);
  return combox;
}

QSlider *Painting::createSlider(int x_move, int y_move, int x_resize,
                                int y_resize) {
  QSlider *slider = new QSlider(Qt::Horizontal, parent_);
  slider->move(x_move, y_move);
  slider->resize(x_resize, y_resize);
  return slider;
}

QLabel *Painting::createLabel(int x_move, int y_move, int x_resize,
                              int y_resize, QString text) {
  QLabel *label = new QLabel(parent_);
  label->move(x_move, y_move);
  label->resize(x_resize, y_resize);
  label->setText(text);
  return label;
}

void Painting::setLabelStyle() {
  labels_[SCALING]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[MOVING]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[ROTATION]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[VERTICES_SETTINGS]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[EDGES_SETTINGS]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[MAIN_SETTINGS]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[INFO]->setStyleSheet(
      "QLabel {color: rgb(0, 0, 0); qproperty-alignment: AlignCenter; font: 63 "
      "13pt URW Bookman;}");
  labels_[INFO_VERTICES_RESULT]->setStyleSheet(
      "QLabel {qproperty-alignment: AlignRight;}");
  labels_[INFO_POLYGONS_RESULT]->setStyleSheet(
      "QLabel {qproperty-alignment: AlignRight;}");
  labels_[INFO_PATH_RESULT]->setStyleSheet(
      "QLabel {qproperty-alignment: AlignRight;}");
}

void Painting::createComboxesText() {
  setComboxText(comboxes_[VERTEX_COLOR],
                {"BLACK", "WHITE", "RED", "GREEN", "BLUE"});
  setComboxText(comboxes_[VERTEX_TYPE], {"MISSING", "CIRCLE", "SQUARE"});
  setComboxText(comboxes_[LINE_COLOR],
                {"BLACK", "WHITE", "RED", "GREEN", "BLUE"});
  setComboxText(comboxes_[LINE_TYPE], {"SOLID", "DOTTED"});
  setComboxText(comboxes_[MAIN_COLOR],
                {"WHITE", "BLACK", "RED", "GREEN", "BLUE"});
  setComboxText(comboxes_[MAIN_TYPE], {"CENTRAL", "PARALLEL"});
}

void Painting::settingSliders() {
  sliders_[LINE_SIZE]->setRange(1, 5);
  sliders_[SCALE]->setRange(0, 50);
  sliders_[SCALE]->setValue(25);
  sliders_[ROTATE]->setRange(-45, 45);
  sliders_[ROTATE]->setValue(0);
  sliders_[SHIFT]->setRange(-50, 50);
  sliders_[SHIFT]->setValue(0);
  sliders_[VERTEX_SIZE]->setRange(0, 10);
}

void Painting::setComboxText(QComboBox *combox, std::vector<QString> elements) {
  for (int i = 0; i < (int)elements.size(); i++) {
    combox->addItem(elements[i]);
  }
}

int Painting::changeVertexType(const QString &text) {
  int vertex_type;
  if (text == "MISSING") {
    vertex_type = 0;
  } else if (text == "SQUARE") {
    vertex_type = 1;
  } else {
    vertex_type = 2;
  }
  return vertex_type;
}

int Painting::changeLineType(const QString &text) {
  int line_type;
  if (text == "SOLID") {
    line_type = 0xFFFF;
  } else {
    line_type = 0x00FF;
  }
  return line_type;
}

int Painting::changeMainType(const QString &text) {
  int projection;
  if (text == "CENTRAL") {
    projection = 1;
  } else {
    projection = 0;
  }
  return projection;
}

void Painting::findAndSetColor(const QString &text, int &first, int &second,
                               int &third) {
  if (text == "BLACK") {
    first = 0;
    second = 0;
    third = 0;
  } else if (text == "WHITE") {
    first = 255;
    second = 255;
    third = 255;
  } else if (text == "BLUE") {
    first = 0;
    second = 0;
    third = 255;
  } else if (text == "RED") {
    first = 255;
    second = 0;
    third = 0;
  } else {
    first = 0;
    second = 255;
    third = 0;
  }
}

QPushButton *Painting::getButton(int i) { return push_buttons_[i]; }

QSlider *Painting::getSlider(int i) { return sliders_[i]; }

QComboBox *Painting::getComBox(int i) { return comboxes_[i]; }

std::string Painting::createFilePath() {
  std::string path;
  QString q_path =
      QFileDialog::getOpenFileName(parent_, "open file", "/", "*.obj");
  if (q_path.length()) {
    labels_[INFO_PATH_RESULT]->setText(q_path);
    QByteArray b_path = q_path.toLatin1();
    path = b_path.data();
  }
  return path;
}

void Painting::setSettingsInFile() {
  std::ofstream file;
  file.open(
      (QDir::homePath() + "/CPP4_3DViewer_v2.0-0/src/S21_3DViewer/settings.cfg")
          .toLocal8Bit()
          .constData());
  if (!file) throw std::out_of_range("Do not such file or directory!");
  file << comboxes_[VERTEX_TYPE]->currentText().toLocal8Bit().constData()
       << std::endl;
  file << QString::number(sliders_[VERTEX_SIZE]->value())
              .toLocal8Bit()
              .constData()
       << std::endl;
  file << comboxes_[VERTEX_COLOR]->currentText().toLocal8Bit().constData()
       << std::endl;
  file << comboxes_[LINE_TYPE]->currentText().toLocal8Bit().constData()
       << std::endl;
  file
      << QString::number(sliders_[LINE_SIZE]->value()).toLocal8Bit().constData()
      << std::endl;
  file << comboxes_[LINE_COLOR]->currentText().toLocal8Bit().constData()
       << std::endl;
  file << comboxes_[MAIN_TYPE]->currentText().toLocal8Bit().constData()
       << std::endl;
  file << comboxes_[MAIN_COLOR]->currentText().toLocal8Bit().constData()
       << std::endl;
  file.close();
}

}  // namespace s21
