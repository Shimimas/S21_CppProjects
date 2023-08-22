#include "s21_matrix_oop.h"

namespace s21 {

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect input, index is out of range");
  }
  cols_ = cols;
  rows_ = rows;
  MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryAllocation();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    RemoveMatrix();
  }
  cols_ = 0;
  rows_ = 0;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  MemoryAllocation();
  CopyMatrix(this, other);

  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); }

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Error: Columns matrix A should be equal rows matrix B");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      double res = 0;
      for (int k = 0; k < cols_; k++) {
        res += (*this).GetElement(i, k) * other.GetElement(k, j);
      }
      result.SetElement(i, j, res);
    }
  }
  *this = result;
}

double S21Matrix::GetElement(int i, int j) const {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i][j];
}

void S21Matrix::SetElement(int i, int j, double value) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  matrix_[i][j] = value;
}

void S21Matrix::MemoryAllocation() {
  matrix_ = new double*[rows_];
  if (matrix_) {
    for (int i = 0; i < rows_; i += 1) {
      matrix_[i] = new double[cols_];
    }
  }
  FillMatrix(0);
}

void S21Matrix::FillMatrix(double iterator) {
  double iter = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      iter += iterator;
      matrix_[i][j] = iter;
    }
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void S21Matrix::CopyMatrix(S21Matrix* dst, const S21Matrix& src) {
  if (dst->matrix_) {
    for (int i = 0; i < dst->rows_; i++) delete[] dst->matrix_[i];
    delete[] dst->matrix_;
    dst->matrix_ = nullptr;
  }
  dst->rows_ = src.rows_;
  dst->cols_ = src.cols_;
  dst->MemoryAllocation();
  for (int i = 0; i < dst->rows_; i += 1) {
    for (int j = 0; j < dst->cols_; j += 1) {
      dst->matrix_[i][j] = src.matrix_[i][j];
    }
  }
}

double** S21Matrix::GetMatrix() const { return matrix_; }

}  // namespace s21
