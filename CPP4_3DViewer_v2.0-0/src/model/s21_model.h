#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>

#include "s21_matrix_oop.h"

#define ALLOCATION_BLOCK 3

namespace s21 {
class Model {
 public:
  class ModelIterator {
   public:
    float *current = nullptr;

    explicit ModelIterator(float *init) : current(init){};
    ModelIterator operator+(int n) { return ModelIterator(current + n); }
    ModelIterator operator-(int n) { return ModelIterator(current - n); }
    ModelIterator operator++() { return ModelIterator(++current); }
    ModelIterator operator--() { return ModelIterator(--current); }

    bool operator==(const ModelIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ModelIterator &other) const {
      return current != other.current;
    }

    float operator*() { return *current; }
    float operator=(float value) { return *current = value; }
  };

  static Model &ModelInstance();

  float *GetVertexArray();
  unsigned int *GetPolygonArray();
  int GetPolygonsAmount();
  int GetPolygonsCount();
  int GetVerticesAmount();
  int GetError();

  Model::ModelIterator EndVertexArray();
  Model::ModelIterator BeginVertexArray();

  void Parsing(std::string file_path);

  void ClearModel();
  void Scale(double transformation_corner);
  void Shift(double transformation_corner, char transformation_axis);
  void TurnAround(double transformation_corner, char transformation_axis);

 private:
  Model() = default;
  Model(std::string *file_path) = delete;
  Model(const Model &other) = delete;
  Model(Model &&other) = delete;
  ~Model() = default;

  int polygons_count_ = 0;
  int polygons_amount_ = 0;
  int vertices_amount_ = 0;
  int polygon_alloc_block_ = 0;
  int error_ = 0;

  double max_abs_coordination_ = 0;

  unsigned int *polygon_array_ = nullptr;
  float *vertex_array_ = nullptr;

  void TurnAroundShift(double transformation_corner, int transformation_type);
  void ParseString(std::string current_string, char string_type);
  void AddToVertex(std::string current_string, double *tmp_digit,
                   double *degree, int *current_vertex, bool *digit);
  void AddToPolygon(std::string current_string, double *tmp_digit,
                    int *current_polygons, bool *digit, bool *bracket);

  Model &operator=(const Model &other) = delete;
  Model &operator=(Model &&other) = delete;
};
}  // namespace s21
