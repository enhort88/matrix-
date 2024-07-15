#include "s21_matrix_exception.h"

MatrixException::MatrixException(const std::string& message)
    : message_(message){};

void MatrixException::addMessage(const std::string& additionalMessage) {
  std::ostringstream oss;
  oss << message_ << " -> " << additionalMessage;
  message_ = oss.str();
}

const char* MatrixException::what() const noexcept { return message_.c_str(); }
