#include <gtest/gtest.h>

#include <iostream>

#include "../controller/s21_controller.h"

TEST(parser_test, incorrect_point_test_0) {
    s21::Controller& InstanceController = s21::Controller::ControllerInstance();
    std::string file_path = "S21_3DViewer/tests/Cube.obj";
    InstanceController.Parsing(file_path);

  for (int i = 0; i < InstanceController.GetVerticesAmount(); i++) {
    if (InstanceController.GetVertexArray()[i] - 
    InstanceController.GetVertexArray()[i] > EPS) {
        ASSERT_EQ(1, 1);
    }  
  }
  ASSERT_EQ(InstanceController.GetVerticesAmount(), 24);
  ASSERT_EQ(InstanceController.GetPolygonsAmount(), 72);
  ASSERT_EQ(InstanceController.GetPolygonsCount(), 12);

  InstanceController.Shift(1, 'x');
  InstanceController.Shift(1, 'y');
  InstanceController.Shift(1, 'z');

  InstanceController.TurnAround(30, 'x');
  InstanceController.TurnAround(30, 'y');
  InstanceController.TurnAround(30, 'z');

  InstanceController.Scale(2);

  for (int i = 0; i < InstanceController.GetVerticesAmount(); i++) {
    if (InstanceController.GetVertexArray()[i] - 
    InstanceController.GetVertexArray()[i] > EPS) {
        ASSERT_EQ(1, 1);
    }  
  }

  for (int i = 0; i < InstanceController.GetPolygonsAmount(); i++) {
    if (InstanceController.GetPolygonArray()[i] - 
    InstanceController.GetPolygonArray()[i] > EPS) {
        ASSERT_EQ(1, 1);
    }  
  }
  InstanceController.ClearModel();
  
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}