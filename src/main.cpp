#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

int main() {
  try {
    S21Matrix mat(3, 3);
    mat(0, 0) = 2;
    mat(0, 1) = 3;
    mat(0, 2) = 1;
    mat(1, 0) = 4;
    mat(1, 1) = 5;
    mat(1, 2) = 7;
    mat(2, 0) = 6;
    mat(2, 1) = 8;
    mat(2, 2) = 9;

    S21Matrix minor(2, 2);
    mat.Minor(minor, 1, 1);

    std::cout << "Minor matrix:\n";
    minor.print();
    std::cout << "Determinante matrix: " << mat.Determinant()<< std::endl;

    S21Matrix complements = mat.CalcComplements();
        std::cout << "Complements matrix:\n";
        complements.print();


  } catch (const MatrixException &err) {
    std::cerr << "\nMatrix Exception: " << err.what() << std::endl;
  }
  // S21Matrix o(p);
  // std::cout << "o "<<o(0,0) << std::endl;
  // p(1,1) = 18;
  //  std::cout <<"p2 " << p(0,0) << std::endl;
  // std::cout << "o2 "<<o(0,0) << std::endl;
  return 0;
}