#ifndef S21_MATRIX_PLUS
#define S21_MATRIX_PLUS


#include <iostream> 
#include <cmath>
#include <cstring>

#define EPS 1e-07

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void createMatrix();
  void deleteMatrix();
//   void cutMatrix(S21Matrix&, S21Matrix&, int&, int&);
//   S21Matrix cut2Matrix(const int& i, const int& j);

 public:

  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int getCols() const;
  int getRows() const;
  void setRows(int rows);
  void setCols(int cols);
  const double** getMatrix() const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double Determinant();

  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other) const;

  double& operator()(const int row, const int col);
  const double& operator()(const int row, const int col) const;
};
std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix);

#endif  // S21_MATRIX_PLUS