#ifndef PAINTING_H
#define PAINTING_H

#include <QComboBox>
#include <QDate>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <fstream>

#include "qgifimage.h"

namespace s21 {

typedef enum {
  OPEN_BUTTON = 0,
  SCREENSHOT_BUTTON = 1,
  GIF_BUTTON = 2,
  X_MOVING_BUTTON = 3,
  Y_MOVING_BUTTON = 4,
  Z_MOVING_BUTTON = 5,
  X_ROTATE_BUTTON = 6,
  Y_ROTATE_BUTTON = 7,
  Z_ROTATE_BUTTON = 8
} button_t;

typedef enum {
  SCALE = 0,
  ROTATE = 1,
  SHIFT = 2,
  VERTEX_SIZE = 3,
  LINE_SIZE = 4
} sliders_t;

typedef enum {
  VERTEX_COLOR = 0,
  LINE_COLOR = 1,
  MAIN_COLOR = 2,
  VERTEX_TYPE = 3,
  LINE_TYPE = 4,
  MAIN_TYPE = 5
} comboxes_t;

typedef enum {
  VERTICES_SETTINGS = 0,
  VERTICES_SETTINGS_TYPE = 1,
  VERTICES_SETTINGS_SIZE = 2,
  VERTICES_SETTINGS_COLOR = 3,
  EDGES_SETTINGS = 4,
  EDGES_SETTINGS_TYPE = 5,
  EDGES_SETTINGS_SIZE = 6,
  EDGES_SETTINGS_COLOR = 7,
  MAIN_SETTINGS = 8,
  MAIN_SETTINGS_PROJECTION = 9,
  MAIN_SETTINGS_COLOR = 10,
  INFO = 11,
  INFO_VERTICES = 12,
  INFO_POLYGONS = 13,
  INFO_PATH = 14,
  SCALING = 15,
  MOVING = 16,
  ROTATION = 17,
  INFO_VERTICES_RESULT = 18,
  INFO_POLYGONS_RESULT = 19,
  INFO_PATH_RESULT = 20
} labels_t;

class Painting {
 public:
  Painting(QWidget *parent = nullptr);

  QPushButton *getButton(int i);
  QSlider *getSlider(int i);
  QComboBox *getComBox(int i);

  const int *getStartingSettings();
  const int *createIntSettingsArray(const std::vector<QString> result_string);
  std::string createFilePath();

  int changeVertexType(const QString &text);
  int changeLineType(const QString &text);
  int changeMainType(const QString &text);
  void findAndSetColor(const QString &text, int &first, int &second,
                       int &third);

  void setSettingsInFile();

 private:
  QWidget *parent_;

  QPushButton *push_buttons_[9];
  QSlider *sliders_[5];
  QLabel *labels_[21];
  QComboBox *comboxes_[6];

  void placeAndSettingAllElements();

  void placeAllElements();
  void setComboxText(QComboBox *combox, std::vector<QString> elements);

  void setLabelStyle();
  void settingCentralWidget();
  void createComboxesText();
  void settingSliders();

  QPushButton *createButton(int x_move, int y_move, int x_resize, int y_resize,
                            QString text);
  QComboBox *createCombox(int x_move, int y_move, int x_resize, int y_resize);
  QSlider *createSlider(int x_move, int y_move, int x_resize, int y_resize);
  QLabel *createLabel(int x_move, int y_move, int x_resize, int y_resize,
                      QString text);

  void setStartWidgetsSettings(const std::vector<QString> result_string);
};

}  // namespace s21

#endif  // PAINTING_H
