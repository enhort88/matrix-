#include "s21_matrix_exception.h"
#include "s21_matrix_oop.h"

int main() {
  try {
    S21Matrix p1(1, 1);
    S21Matrix p2(1, 1);

    p1(0, 0) = 15;
    p2(0, 0) = 15;

    std::cout << "p " << p1(1, 1) << std::endl;
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