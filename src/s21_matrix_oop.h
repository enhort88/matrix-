#ifndef S21_MATRIX_PLUS
#define S21_MATRIX_PLUS


#include <iostream> 
#include <cmath>
#include <cstring>
#include <vector>
#include <stdexcept>

#define EPS 1e-07

class S21Matrix {
 private:
    std::vector<std::vector<double>> matrix_;
    int rows_, cols_;

 public:

  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);
  //const double** getMatrix() const;

  void createMatrix();
  void deleteMatrix();
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other) ;

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  double Determinant();

  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) ;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) ;
  S21Matrix& operator*=(const S21Matrix& other) ;
  S21Matrix operator*(const S21Matrix& other) ;
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const double num) ;
  bool operator==(const S21Matrix& other) const;
  double& operator()(const int row, const int col);
  const double& operator()(const int row, const int col) const;
};
std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix);

#endif  // S21_MATRIX_PLUS