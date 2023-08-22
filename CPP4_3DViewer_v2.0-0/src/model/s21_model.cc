#include "s21_model.h"

namespace s21 {

Model &Model::ModelInstance() {  // Myers singleton
  static Model Singleton;
  return Singleton;
}

float *Model::GetVertexArray() { return vertex_array_; }

unsigned int *Model::GetPolygonArray() { return polygon_array_; }

int Model::GetPolygonsAmount() { return polygons_amount_; }

int Model::GetVerticesAmount() { return vertices_amount_; }

int Model::GetError() { return error_; }

int Model::GetPolygonsCount() { return polygons_count_; }

void Model::Parsing(std::string file_path) {
  error_ = 0;
  std::ifstream fin;
  fin.open(file_path);
  std::cout << file_path << std::endl;
  if (!fin.is_open()) {
    error_ = 1;
  } else {
    char symbol;
    bool found_flag = 0;
    int digit = 0, for_swap = 0;
    std::string current_string = "";
    while (!fin.eof()) {
      std::getline(fin, current_string, '\n');
      symbol = current_string[0];
      switch (symbol) {
        case 'v':
          if (current_string[1] != 'f' && current_string[1] != 'n' &&
              current_string[1] != 'p') {
            ParseString(current_string + "\n", symbol);
          }
          break;
        case 'f':
          if (!found_flag) {
            for (int i = 1; i < (int)current_string.size(); i++) {
              if (current_string[i] >= '0' && current_string[i] <= '9') {
                digit = 1;
              } else if (current_string[i] == ' ' ||
                         current_string[i] == '\n') {
                if (digit) {
                  polygon_alloc_block_ += 1;
                  digit = 0;
                }
              }
            }
            polygon_alloc_block_ += 1;
            found_flag = 1;
          }
          ParseString(current_string + "\n", symbol);
          break;
        default:
          break;
      }
    }
    max_abs_coordination_ += 0.05;
    for (auto it = BeginVertexArray(); it != EndVertexArray(); ++it) {
      it = *it / max_abs_coordination_;
    }
    for (int i = 0; i < polygons_amount_; i++) {
      if (i % 2 == 1) {
        if ((for_swap + 1) % (polygon_alloc_block_ * 2) ==
            (polygon_alloc_block_ * 2 - 1)) {
          polygon_array_[i] =
              polygon_array_[for_swap - (polygon_alloc_block_ * 2 - 2)];
          std::swap(polygon_array_[i - 1], polygon_array_[i]);
        } else {
          polygon_array_[i] = polygon_array_[i + 1];
        }
        for_swap += 2;
      }
    }
  }
  fin.close();
}

void Model::ParseString(std::string current_string, char string_type) {
  double tmp_digit = 0, degree = -1;
  bool digit = 0, bracket = 0;
  int current_vertex = vertices_amount_, current_polygons = polygons_amount_;
  if (string_type == 'v') {
    vertex_array_ = (float *)realloc(
        vertex_array_, sizeof(float) * (current_vertex + ALLOCATION_BLOCK));
    AddToVertex(current_string, &tmp_digit, &degree, &current_vertex, &digit);
    vertices_amount_ += ALLOCATION_BLOCK;
  } else if (string_type == 'f') {
    polygon_array_ = (unsigned int *)realloc(
        polygon_array_,
        sizeof(unsigned int) * (polygons_amount_ + (polygon_alloc_block_ * 2)));
    AddToPolygon(current_string, &tmp_digit, &current_polygons, &digit,
                 &bracket);
    polygons_amount_ += (polygon_alloc_block_ * 2);
    polygons_count_ += 1;
  }
}

void Model::AddToVertex(std::string current_string, double *tmp_digit,
                        double *degree, int *current_vertex, bool *digit) {
  bool dot = 0, minus = 0;
  for (int i = 1; i < (int)current_string.size(); i++) {
    if (current_string[i] >= '0' && current_string[i] <= '9') {
      *digit = 1;
      if (dot) {
        *tmp_digit += (current_string[i] - '0') * pow(10, (*degree)--);
      } else {
        *tmp_digit *= 10;
        *tmp_digit += (current_string[i] - '0');
      }
    } else if (current_string[i] == '.') {
      dot = 1;
    } else if (current_string[i] == '-') {
      minus = 1;
    } else if (current_string[i] == ' ' || current_string[i] == '\n') {
      if (*digit) {
        if (minus) {
          *tmp_digit *= -1;
          minus = 0;
        }
        vertex_array_[*current_vertex] = *(tmp_digit);
        if (abs(vertex_array_[*current_vertex]) > max_abs_coordination_) {
          max_abs_coordination_ = abs(vertex_array_[*current_vertex]);
        }
        *tmp_digit = 0, *digit = 0, *degree = -1, dot = 0;
        *current_vertex += 1;
      }
    }
  }
}

void Model::AddToPolygon(std::string current_string, double *tmp_digit,
                         int *current_polygons, bool *digit, bool *bracket) {
  for (int i = 1; i < (int)current_string.size(); i++) {
    if (current_string[i] >= '0' && current_string[i] <= '9' && !*bracket) {
      *digit = 1;
      *tmp_digit *= 10;
      *tmp_digit += (current_string[i] - '0');
    } else if (current_string[i] == '/') {
      *bracket = 1;
    } else if (current_string[i] == ' ' || current_string[i] == '\n') {
      if (*digit) {
        polygon_array_[*current_polygons] = (*tmp_digit) - 1;
        polygon_array_[*current_polygons + 1] = 0;
        *tmp_digit = 0, *digit = 0, *bracket = 0;
        *current_polygons += 2;
      }
    }
  }
}

void Model::TurnAroundShift(double transformation_corner,
                            int transformation_type) {
  if (transformation_type >= 0 && transformation_type <= 2) {
    transformation_corner = (transformation_corner * M_PI) / 180;
  } else if (transformation_type == 6) {
    transformation_corner = pow(transformation_corner, 1.0 / 3.0);
  }
  int i_idx, j_idx;
  if (transformation_type == 0) {
    i_idx = 1;
    j_idx = 2;
  } else if (transformation_type == 1) {
    i_idx = 2;
    j_idx = 0;
  } else if (transformation_type == 2) {
    i_idx = 0;
    j_idx = 1;
  }
  for (int m = 0, m_e = 0; m < vertices_amount_;) {
    S21Matrix MatrixA(4, 4), MatrixB(4, 1);
    for (int i = 0; i < 4; i++) {
      if (i == 3) {
        MatrixB.SetElement(i, 0, 1);
      } else {
        MatrixB.SetElement(i, 0, vertex_array_[m++]);
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i == j) {
          if (transformation_type == 6) {
            if (j == 3) {
              MatrixA.SetElement(i, j, 1);
            } else {
              MatrixA.SetElement(i, j, transformation_corner);
            }
          } else {
            MatrixA.SetElement(i, j, 1);
          }
        } else {
          MatrixA.SetElement(i, j, 0);
        }
      }
    }
    if (transformation_type >= 0 && transformation_type <= 2) {
      MatrixA.SetElement(i_idx, i_idx, cos(transformation_corner));
      MatrixA.SetElement(j_idx, j_idx, cos(transformation_corner));
      MatrixA.SetElement(i_idx, j_idx, sin(transformation_corner) * -1);
      MatrixA.SetElement(j_idx, i_idx, sin(transformation_corner));
    } else if (transformation_type == 3) {  // x
      MatrixA.SetElement(0, 3, transformation_corner);
    } else if (transformation_type == 4) {  // y
      MatrixA.SetElement(1, 3, transformation_corner);
    } else if (transformation_type == 5) {  // z
      MatrixA.SetElement(2, 3, transformation_corner);
    }
    S21Matrix ResultMatrix(4, 4);
    ResultMatrix = MatrixA * MatrixB;
    for (int i = 0; i < ResultMatrix.GetRows() - 1; i++) {
      for (int j = 0; j < ResultMatrix.GetCols(); j++) {
        vertex_array_[m_e++] = ResultMatrix.GetMatrix()[i][j];
      }
    }
  }
}

void Model::Scale(double transformation_corner) {
  TurnAroundShift(transformation_corner, 6);
}

void Model::Shift(double transformation_corner, char transformation_axis) {
  switch (transformation_axis) {
    case 'x':
      TurnAroundShift(transformation_corner, 3);
      break;
    case 'y':
      TurnAroundShift(transformation_corner, 4);
      break;
    case 'z':
      TurnAroundShift(transformation_corner, 5);
      break;
  }
}

void Model::TurnAround(double transformation_corner, char transformation_axis) {
  switch (transformation_axis) {
    case 'x':
      TurnAroundShift(transformation_corner, 0);
      break;
    case 'y':
      TurnAroundShift(transformation_corner, 1);
      break;
    case 'z':
      TurnAroundShift(transformation_corner, 2);
      break;
  }
}

Model::ModelIterator Model::EndVertexArray() {
  return ModelIterator(vertex_array_ + vertices_amount_);
}

Model::ModelIterator Model::BeginVertexArray() {
  return ModelIterator(vertex_array_);
}

void Model::ClearModel() {
  for (int i = 0; i < polygons_amount_; i++) {
    polygon_array_[i] = 0;
  }
  for (int i = 0; i < vertices_amount_; i++) {
    vertex_array_[i] = 0;
  }
  polygons_count_ = 0;
  polygons_amount_ = 0;
  vertices_amount_ = 0;
  polygon_alloc_block_ = 0;
  max_abs_coordination_ = 0;
  error_ = 0;
}

}  // namespace s21
