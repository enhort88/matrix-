#ifndef S21_MATRIX_PLUS
#define S21_MATRIX_PLUS

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

#define EPS 1e-07

class S21Matrix {
 private:
  int rows_, cols_;
  std::vector<std::vector<double>> matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);
  void set_element(int row, int col, double value);
  double get_element(int row, int col) const;
  // void print() const;

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  void isCorrect(const S21Matrix &other);

  void Minor(S21Matrix &minor, int r, int c);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix Transpose();
  S21Matrix InverseMatrix();

  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  double &operator()(const int row, const int col);
};

#endif  // S21_MATRIX_PLUS