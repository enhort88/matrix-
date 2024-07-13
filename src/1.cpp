#include <iostream>
#include <algorithm>

class Matrix {
private:
    int rows_, cols_;
    double* data_;

public:
    // Конструктор
    Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        data_ = new double[rows_ * cols_];
        std::fill(data_, data_ + rows_ * cols_, 0.0);
        std::cout << "Constructor: Created matrix " << rows_ << "x" << cols_ << std::endl;
    }

    // Конструктор перемещения
    Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
        std::cout << "Move Constructor: Moved matrix " << rows_ << "x" << cols_ << std::endl;
    }

    // Деструктор
    ~Matrix() {
        delete[] data_;
        std::cout << "Destructor: Destroyed matrix " << rows_ << "x" << cols_ << std::endl;
    }

    // Оператор присваивания перемещением
    Matrix& operator=(Matrix&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
        std::cout << "Move Assignment Operator: Moved matrix " << rows_ << "x" << cols_ << std::endl;
        return *this;
    }

    // Метод для получения размеров матрицы
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    double* getData() const { return data_; }
};

// Функция, возвращающая временный объект матрицы
Matrix createMatrix(int rows, int cols) {
    Matrix temp(rows, cols);
    return temp;  // Возвращение временного объекта
}

int main() {

      // Перемещение матрицы
    Matrix m4 = createMatrix(4, 4);  // Вызов конструктора перемещения

    // Присваивание перемещением
    Matrix m5(2, 2);
    m5 = createMatrix(5, 5);  // Вызов оператора присваивания перемещением

    // Проверка состояния матриц
    std::cout << "m4: " << m4.getRows() << "x" << m4.getCols() << " Data: " << m4.getData() << std::endl;
    std::cout << "m5: " << m5.getRows() << "x" << m5.getCols() << " Data: " << m5.getData() << std::endl;

    return 0;
}
