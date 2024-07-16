#ifndef S21_MATRIX_EXCEP
#define S21_MATRIX_EXCEP

//#include <iostream>
#include <sstream>

class MatrixException : public std::exception {
private:
  std::string message_;

public:
  explicit MatrixException(const std::string &message);
  void addMessage(const std::string &additionalMessage);
  const char *what() const noexcept override;
};

#endif // S21_MATRIX_EXCEP
