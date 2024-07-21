#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

int main() {
  int res = 0;
  try {
    //   S21Matrix mat(3, 3);
    //   mat(0, 0) = 2;
    //   mat(0, 1) = 3;
    //   mat(0, 2) = 1;
    //   mat(1, 0) = 4;
    //   mat(1, 1) = 5;
    //   mat(1, 2) = 7;
    //   mat(2, 0) = 6;
    //   mat(2, 1) = 8;
    //   mat(2, 2) = 9;

    //   S21Matrix minor(2, 2);
    //   mat.Minor(minor, 1, 1);

    //   std::cout << "Minor matrix:\n";
    //   minor.print();
    //   std::cout << "Determinante matrix: " << mat.Determinant() << std::endl;

    //   S21Matrix complements = mat.CalcComplements();
    //   std::cout << "Complements matrix:\n";
    //   complements.print();

    //   S21Matrix mat1(3, 3);
    //   mat1(0, 0) = 2;
    //   mat1(0, 1) = 3;
    //   mat1(0, 2) = 1;
    //   mat1(1, 0) = 4;
    //   mat1(1, 1) = 5;
    //   mat1(1, 2) = 7;
    //   mat1(2, 0) = 6;
    //   mat1(2, 1) = 8;
    //   mat1(2, 2) = 9;

    //   std::cout << "Original matrix:\n";
    //   mat1.print();

    //   S21Matrix transposed = mat1.Transpose();

    //   std::cout << "Transposed matrix:\n";
    //   transposed.print();

    //   // InverseMatrix
    //   S21Matrix mat2(3, 3);
    //   mat2(0, 0) = 2;
    //   mat2(0, 1) = 5;
    //   mat2(0, 2) = 7;
    //   mat2(1, 0) = 6;
    //   mat2(1, 1) = 3;
    //   mat2(1, 2) = 4;
    //   mat2(2, 0) = 5;
    //   mat2(2, 1) = -2;
    //   mat2(2, 2) = -3;
    //   std::cout << "Original matrix:\n";
    //  mat2.print();

    //   S21Matrix inverse = mat2.InverseMatrix();
    //   std::cout << "Inverse matrix:\n";
    //   inverse.print();

    // S21Matrix m1(3, 3);
    // m1.set_element(0,0,1);
    // m1.set_element(0,1,1);
    // m1.set_element(1,0,1);
    // m1.set_element(1,1,1);
    // std::cout <<"m1 \n";
    // m1.print();
    // S21Matrix m2(std::move(m1));
    // std::cout <<"\nm2 ";
    // m2.print();

  } catch (const MatrixException &err) {
    res = 11;
    std::cerr << "\nMatrix Exception: " << err.what() << std::endl;
  } catch (const std::exception &err) {
    res = 22;
    std::cerr << "\nMatrix Exception: " << err.what() << std::endl;
  } catch (...) {
    res = 99;
    std::cerr << "\nMatrix Exception: "
              << "Unknown Error" << std::endl;
  }
  return res;
}