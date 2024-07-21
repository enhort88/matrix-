#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw MatrixException("Constructor: Matrix cols/rows out of range");
  matrix_.resize(rows_, std::vector<double>(cols_, 0.0));
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  isCorrect(*this);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  isCorrect(*this);
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {}

int S21Matrix::get_rows() const { return rows_; }
int S21Matrix::get_cols() const { return cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows <= 0)
    throw MatrixException(
        "set_rows : Number of rows must be greater than zero.");
  rows_ = rows;
  matrix_.resize(rows_);
  for (auto &row : matrix_) {
    row.resize(cols_, 0.0);
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw MatrixException(
        "set_cols: Number of columns must be greater than zero.");
  }
  cols_ = cols;
  for (auto &row : matrix_) {
    row.resize(cols_, 0.0);
  }
}
void S21Matrix::set_element(int row, int col, double value) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw MatrixException("set_element: Index out of range");
  }
  matrix_[row][col] = value;
}

double S21Matrix::get_element(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw MatrixException("get_element: Index out of range");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  isCorrect(*this);
  isCorrect(other);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  isCorrect(*this);
  isCorrect(other);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  if (cols_ != other.rows_) {
    throw MatrixException(
        "Operator*: Matrices dimensions do not match for multiplication.");
  }
  isCorrect(*this);
  isCorrect(other);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result(*this);
  isCorrect(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  isCorrect(other);
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
  isCorrect(other);
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  isCorrect(*this);
  isCorrect(other);
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  isCorrect(*this);
  isCorrect(other);
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  isCorrect(*this);
  isCorrect(other);
  *this = *this * other;
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  isCorrect(*this);
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  isCorrect(*this);
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw MatrixException("Operator(): Index out of bounds.");

  return matrix_[i][j];
}

void S21Matrix::isCorrect(const S21Matrix &other) {
  if (other.matrix_.empty())
    throw MatrixException("isCorrect: Matrix is empty");
  if (other.rows_ < 0 || other.cols_ < 0)
    throw MatrixException(
        "isCorrect: Matrix is incorect. Problem with rows/cols");
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  isCorrect(*this);
  if (this == &other) {
  } else if ((rows_ != other.rows_ || cols_ != other.cols_)) {
    result = false;
  } else
    for (int i = 0; i < rows_ && result; ++i)
      for (int j = 0; j < cols_ && result; ++j)
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > EPS) result = false;

  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  isCorrect(*this);
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw MatrixException(
        "SumMatrix: Matrices dimensions do not match for addition.");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  isCorrect(*this);
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw MatrixException(
        "SubMatrix: Matrices dimensions do not match for subtraction.");
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw MatrixException(
        "MulMatrix: Matrices dimensions do not match for multiplication.");
  }
  isCorrect(*this);
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; ++k) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::MulNumber(double num) {
  isCorrect(*this);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::Minor(S21Matrix &minor, int r, int c) {
  isCorrect(*this);
  if (rows_ <= 1 || cols_ <= 1)
    throw MatrixException(
        "Minor: Matrix dimensions must be greater than 1 for minors.");
  int m = rows_ - 1;
  int n = cols_ - 1;
  minor.set_rows(m);
  minor.set_cols(n);
  for (int i = 0, x = 0; i < m; i++, x++) {
    if (x == r) x++;
    for (int j = 0, y = 0; j < n; j++, y++) {
      if (y == c) y++;
      minor(i, j) = matrix_[x][y];
    }
  }
}

double S21Matrix::Determinant() {
  isCorrect(*this);
  double result = 0.0;
  if (rows_ != cols_)
    throw MatrixException(
        "Determinant: Matrix must be square to compute determinant.");
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; ++i) {
      S21Matrix minor(rows_ - 1, cols_ - 1);
      Minor(minor, 0, i);
      result += matrix_[0][i] * minor.Determinant() * (i % 2 == 0 ? 1 : -1);
    }
  }
  return result;
}
S21Matrix S21Matrix::CalcComplements() {
  isCorrect(*this);
  if (rows_ != cols_) {
    throw MatrixException(
        "CalcComplements: Matrix must be square to compute complements.");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = 1;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor(rows_ - 1, cols_ - 1);
        Minor(minor, i, j);
        double det = minor.Determinant();
        result(i, j) = std::pow(-1, i + j) * det;
      }
    }
  }
  return result;
}
S21Matrix S21Matrix::Transpose() {
  isCorrect(*this);
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  isCorrect(*this);
  if (rows_ != cols_) {
    throw MatrixException(
        "InverseMatrix: Matrix must be square to compute the inverse.");
  }
  double det = Determinant();
  if (fabs(det) < 1e-7) {
    throw MatrixException(
        "InverseMatrix: Matrix determinant is 0, the matrix is not "
        "invertible.");
  }
  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  S21Matrix inverse = transposed * (1.0 / det);
  return inverse;
}

// void S21Matrix::print() const {
//   for (int i = 0; i < rows_; ++i) {
//     for (int j = 0; j < cols_; ++j) {
//       std::cout << matrix_[i][j] << " ";
//     }
//     std::cout << std::endl;
//   }
// }