#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <iostream>
#include <cstring>

class S21Matrix {
    
    friend S21Matrix operator*(double num, const S21Matrix &other);
    friend S21Matrix operator*(const S21Matrix &other, double num);

private:

    int rows_ = 0, cols_ = 0;
    double * matrix_ = nullptr;

    void CreateMatrix(int rows, int cols);
    void SetMatrixSize(int rows, int cols);
    void CopyMatrix(const S21Matrix &other);
    void RemoveMatrix();
    void SubOrSumFunction(const S21Matrix& other, int type);
    void MoveMatrix(S21Matrix&& other);
    void GetMinor(int row, int col);

public:

    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    S21Matrix& operator=(const S21Matrix& o);
    S21Matrix& operator=(S21Matrix &&other);
    double& operator()(int row, int col) const;
    double& operator()(int row, int col);
    S21Matrix& operator+=(const S21Matrix& o);                            
    S21Matrix operator+(const S21Matrix& o);
    S21Matrix operator*(const S21Matrix& o);
    S21Matrix& operator-=(const S21Matrix& o);
    S21Matrix operator-(const S21Matrix& o);
    bool operator==(const S21Matrix &other);
    S21Matrix& operator*=(const S21Matrix &other);
    S21Matrix& operator*=(const double &other);

    int GetRows() const;
    int GetCols() const;
    void SetRows(int rows_);
    void SetCols(int cols_);
    double GetMatrix(int rows, int cols) const;
    void SetMatrix(int rows, int cols, double value);

    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

};

#endif
