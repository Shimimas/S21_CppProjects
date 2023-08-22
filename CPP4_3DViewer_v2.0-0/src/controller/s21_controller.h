#pragma once

#include "../model/s21_model.h"

namespace s21 {
class Controller {
 public:
  static Controller& ControllerInstance();

  float* GetVertexArray();
  unsigned int* GetPolygonArray();
  int GetPolygonsCount();
  int GetPolygonsAmount();
  int GetVerticesAmount();

  void Parsing(std::string file_path);

  void ClearModel();
  void Scale(double transformation_corner);
  void Shift(double transformation_corner, char transformation_axis);
  void TurnAround(double transformation_corner, char transformation_axis);

 private:
  Controller() = default;
  Controller(std::string* file_path) = delete;
  Controller(const Controller& other) = delete;
  Controller(Controller&& other) = delete;
  ~Controller() = default;

  Model& InstanceModel = Model::ModelInstance();

  Controller& operator=(const Controller& other) = delete;
  Controller& operator=(Controller&& other) = delete;
};
}  // namespace s21
