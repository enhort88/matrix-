#include "s21_matrix_exception.h"

MatrixException::MatrixException(const std::string &message)
    : message_(message){};

MatrixException &MatrixException::addMessage(
    const std::string &additionalMessage) {
  std::ostringstream oss;
  oss << message_ << " -> " << additionalMessage;
  message_ = oss.str();
  return *this;
}

const char *MatrixException::what() const noexcept { return message_.c_str(); }
