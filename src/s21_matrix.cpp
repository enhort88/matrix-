#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

// Конструкторы и деструктор
S21Matrix::S21Matrix() : rows_(0), cols_(0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw MatrixException("Matrix cols/rows out of range");
  matrix_.resize(rows_, std::vector<double>(cols_, 0.0));
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {}

// Аксессоры и мутаторы
int S21Matrix::get_rows() const { return rows_; }
int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows <= 0)
    throw MatrixException("Number of rows must be greater than zero.");

  rows_ = rows;
  matrix_.resize(rows_);
  for (auto &row : matrix_) {
    row.resize(cols_, 0.0);
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw MatrixException("Number of columns must be greater than zero.");
  }
  cols_ = cols;
  for (auto &row : matrix_) {
    row.resize(cols_, 0.0);
  }
}

// Операции с матрицами
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

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw MatrixException(
        "Matrices dimensions do not match for multiplication.");
  }
  S21Matrix result(rows_, other.cols_);
  S21Matrix temp(other);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.cols_; ++j)
      for (int k = 0; k < cols_; ++k)
        result(i, j) += matrix_[i][k] * temp(k, j);
  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = std::move(other.matrix_);
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
  }
  return *this;
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
  *this = *this * other;
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw MatrixException("Index out of bounds.");
  }
  return matrix_[i][j];
}

// Вспомогательные функции
void S21Matrix::isCorrect(const S21Matrix &other) {
  if (other.matrix_.empty()) throw MatrixException("Matrix is empty");
  if (!other.rows_ || !other.cols_) throw MatrixException("Matrix is incorect. Problem with rows/cols");
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    bool result = false;
    try {
    isCorrect(*this);
    result  = (rows_ == other.rows_) && (cols_ == other.cols_) &&
         (matrix_ == other.matrix_);
  } catch (MatrixException &e) {
    e.addMessage("EqMatrix");
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw MatrixException("Matrices dimensions do not match for addition.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  try {
    isCorrect(*this);
    if (rows_ != other.rows_ || cols_ != other.cols_)
      throw MatrixException(
          "Matrices dimensions do not match for subtraction.");
  } catch (MatrixException &e) {
    e.addMessage("SubMatrix");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  try {
    isCorrect(*this);
    *this = *this * other;
  } catch (MatrixException &e) {
    e.addMessage("Mul Matrix");
  }
}

void S21Matrix::MulNumber(double num) {
  try {
    isCorrect(*this);
  } catch (MatrixException &e) {
    e.addMessage("Mul Number");
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}
double S21Matrix::Determinant() {
  double result = 0;
  try {
    isCorrect(*this);
    if (rows_ != cols_)
      throw MatrixException("Wrong matrix");
    else if (rows_ == 1)
      result = matrix_[0][0];
    else if (rows_ == 2)
      result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    else {
      // todo
    }
  } catch (MatrixException &e) {
    e.addMessage("Determinante");
  }

  return result;
}
