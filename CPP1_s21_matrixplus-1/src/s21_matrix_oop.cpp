#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(3), cols_(3) {
    CreateMatrix(3, 3);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    CreateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        CreateMatrix(rows_, cols_);
        std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    MoveMatrix(std::move(other));
}

S21Matrix::~S21Matrix() {
    RemoveMatrix();
}

int S21Matrix::GetRows() const {
    return rows_;
}

int S21Matrix::GetCols() const {
    return cols_; 
}

void S21Matrix::SetRows(int rows_) {
    SetMatrixSize(rows_, this->cols_);
}

void S21Matrix::SetCols(int cols_) {
    SetMatrixSize(this->rows_, cols_);
}

double S21Matrix::GetMatrix(int rows, int cols) const {
    if (rows >= rows_ || cols >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[rows * cols_ + cols];
}

void S21Matrix::SetMatrix(int rows, int cols, double value) {
    if (rows >= rows_ || cols >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    matrix_[rows * cols_ + cols] = value;
}

void S21Matrix::CreateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::out_of_range("Error: the number of columns or rows is less than or equal to zero");
    }
    try {
        matrix_ = new double[rows * cols]();
    } catch (const std::bad_alloc &ex) {
        std::cout << "Allocation failed: " << ex.what() << std::endl;
    }
}

void S21Matrix::RemoveMatrix() {
    if (rows_ > 0 && cols_ > 0 && matrix_ != nullptr) {
        delete[] matrix_;
    }
    rows_ = 0;
    cols_ = 0;
}

void S21Matrix::SetMatrixSize(int rows, int cols) {
    if (rows != rows_ || cols != cols_) {
        if (rows <= 0 || cols <= 0) {
            throw std::out_of_range("Error: the number of columns or rows is less than or equal to zero");
        }
        S21Matrix tmp = *this;
        RemoveMatrix();
        CreateMatrix(rows, cols);
        rows_ = rows;
        cols_ = cols;
        std::memcpy(matrix_, tmp.matrix_, std::min(tmp.cols_, cols_) * std::min(tmp.rows_, rows_) * sizeof(double));
    }
}

void S21Matrix::SubOrSumFunction(const S21Matrix& other, int type) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }
    if (type == 1) {
        for (int i = 0; i < rows_ * cols_; i++) {
            matrix_[i] = matrix_[i] + other.matrix_[i];
        }
    } else {
        for (int i = 0; i < rows_ * cols_; i++) {
            matrix_[i] = matrix_[i] - other.matrix_[i];
        }
    }
}

void S21Matrix::MoveMatrix(S21Matrix&& other) {
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    other.RemoveMatrix();
}

void S21Matrix::GetMinor(int row, int col) {
    S21Matrix tmp(*this);
    RemoveMatrix();
    rows_ = tmp.rows_ - 1;
    cols_ = tmp.cols_ - 1;
    CreateMatrix(rows_, cols_);
    int z = 0;
    for (int i = 0; i < tmp.rows_; i++) {
        if (i != row) {
            int k = 0;
            for (int j = 0; j < tmp.cols_; j++) {
                if (j != col) {
                    this->SetMatrix(z, k, tmp.GetMatrix(i, j));
                    k++;
                }
            }
            z++;
        }
    }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    SubOrSumFunction(other, 1);
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool result = true;
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        for (int i = 0; i < rows_ * cols_; i++) {
            if (matrix_[i] != other.matrix_[i]) {
                result = false;
            }
        }
    } else {
        result = false;
    }
    return result;
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    SubOrSumFunction(other, 0);
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_ * cols_; i++) {
        matrix_[i] = matrix_[i] * num;
    }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Error: Columns matrix A should be equal rows matrix B");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            double res = 0;
            for (int k = 0; k < cols_; k++) {
                res += (*this).GetMatrix(i, k) * other.GetMatrix(k, j);
            }
            result.SetMatrix(i, j, res);
        }
    }
    *this = result;
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < result.rows_; i++) {
        for (int j = 0; j < result.cols_; j++) {
            result.SetMatrix(i, j, (*this).GetMatrix(j, i));
        }
    }
    return result;
}

double S21Matrix::Determinant() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Error: Matrix should be square");
    }
    double result = 0;
    if (cols_ == 1) {
        result = matrix_[0];
    } else {
        for (int i = 0; i < cols_; i++) {
            S21Matrix tmp(*this);
            tmp.GetMinor(0, i);
            int z = (((i % 2) == 0) ? 1 : -1);
            result += z * (*this).GetMatrix(0, i) * tmp.Determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Error: Matrix should be square");
    }
    S21Matrix result(rows_, cols_);
    if (cols_ == 1) {
        result.matrix_[0] = 1;
    } else {
        for (int i = 0; i < result.rows_; i++) {
            for (int j = 0; j < result.cols_; j++) {
                S21Matrix tmp(*this);
                tmp.GetMinor(i, j);
                int z = (((i + j) % 2) == 0 ? 1 : -1);
                result.SetMatrix(i, j, z * tmp.Determinant());
            }
        }
    }
    return result;
}

S21Matrix S21Matrix::InverseMatrix() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Error: Matrix should be square");
    }
    double det = Determinant();
    if (det == 0) {
        throw std::invalid_argument("Error: Determinant = 0");
    }
    S21Matrix calc = CalcComplements();
    S21Matrix result = calc.Transpose();
    result.MulNumber(1.0 / det);
    return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
    S21Matrix result(*this);
    result.SumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
    S21Matrix result(*this);
    result.SubMatrix(other);
    return result;
}

S21Matrix operator*(double num, const S21Matrix &other) {
    S21Matrix result(other);
    result.MulNumber(num);
    return result;
}

S21Matrix operator*(const S21Matrix &other, double num) {
    S21Matrix result(other);
    result.MulNumber(num);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.MulMatrix(other);
    return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { 
    return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
    SumMatrix(other);
    return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
    SubMatrix(other);
    return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
    MulMatrix(other);
    return *this;
}

S21Matrix &S21Matrix::operator*=(const double &num) {
    MulNumber(num);
    return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
    RemoveMatrix();
    CreateMatrix(other.rows_, other.cols_);
    rows_ = other.rows_;
    cols_ = other.cols_;
    std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
    return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
    RemoveMatrix();
    MoveMatrix(std::move(other));
    return *this;
}

double& S21Matrix::operator()(int row, int col) {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[row * cols_ + col];
}

double& S21Matrix::operator()(int row, int col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }
    return matrix_[row * cols_ + col];
}