#include "s21_controller.h"

namespace s21 {
Controller &Controller::ControllerInstance() {
  static Controller Singleton;
  return Singleton;
}

void Controller::Parsing(std::string file_path) {
  InstanceModel.Parsing(file_path);
}

void Controller::Scale(double transformation_corner) {
  InstanceModel.Scale(transformation_corner);
}

void Controller::Shift(double transformation_corner, char transformation_axis) {
  InstanceModel.Shift(transformation_corner, transformation_axis);
}

void Controller::TurnAround(double transformation_corner,
                            char transformation_axis) {
  InstanceModel.TurnAround(transformation_corner, transformation_axis);
}

void Controller::ClearModel() { InstanceModel.ClearModel(); }

float *Controller::GetVertexArray() { return InstanceModel.GetVertexArray(); }

int Controller::GetPolygonsCount() { return InstanceModel.GetPolygonsCount(); }

unsigned int *Controller::GetPolygonArray() {
  return InstanceModel.GetPolygonArray();
}

int Controller::GetPolygonsAmount() {
  return InstanceModel.GetPolygonsAmount();
}

int Controller::GetVerticesAmount() {
  return InstanceModel.GetVerticesAmount();
}

}  // namespace s21
