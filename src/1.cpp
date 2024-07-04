#include <iomanip>
#include <iostream>  

int main() {
    int x = 1;
    int rows = 2;
    int cols = 2;

    // Выделение памяти для одномерного массива, представляющего двумерный массив
    double* matrix = new double[rows * cols]();

    // Заполнение массива
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i * cols + j] = x++;
        }
    }

    // Вывод массива
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождение памяти
    delete[] matrix;

    return 0;
}
