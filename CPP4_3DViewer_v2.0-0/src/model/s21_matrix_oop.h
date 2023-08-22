#pragma once

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace s21 {

#define EPS 1e-7

#define SUCCESS 1
#define FAILURE 0

typedef enum {
  CORRECT_MATRIX = 0,
  INCORRECT_MATRIX = 1,
  IDENTITY_MATRIX = 2,
  ZERO_MATRIX = 3
} matrix_type_t;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  S21Matrix& operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  void operator*=(const double number);
  S21Matrix operator*(const double number);
  double operator()(int i, int j) const;
  bool operator==(const S21Matrix& other);

  int GetRows() const;
  int GetCols() const;
  double** GetMatrix() const;
  double GetElement(int i, int j) const;
  matrix_type_t GetMatrixType() const;

  void SetRows(int rows_);
  void SetCols(int cols_);
  void SetMatrix(double** matrix_, int rows_, int cols_);
  void SetElement(int i, int j, double data);
  void SetMatrixType(matrix_type_t matrix_type_);

  bool EqMatrix(const S21Matrix& other);

  int IsinfIsnanCheck(double x);

  double Determinant();

  matrix_type_t DefineMatrixType() const;

  S21Matrix Transpose();
  S21Matrix InverseMatrix();
  S21Matrix CalcComplements();
  S21Matrix Minor(int rows, int cols);

  void PrintMatrix() const;
  void RemoveMatrix();
  void FillMatrix(double iterator);
  void AllocHelper(int rows_, int cols_, int type);
  void InitMatrix(int rows, int cols, int type);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MemoryAllocation();
  void ArifmeticMatrix(const S21Matrix& other, int type);
  void CopyMatrix(S21Matrix* dst, const S21Matrix& src);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  void GetMatrix(std::string path);

 private:
  int rows_, cols_;
  double** matrix_;
  matrix_type_t matrix_type_;
};

}  // namespace s21
