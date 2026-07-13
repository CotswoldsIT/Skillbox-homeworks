#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция для ввода матрицы 4x4
void input_matrix(float matrix[4][4]) {
    std::cout << "Введите элементы матрицы A (16 вещественных чисел через пробел):\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

// Функция для ввода вектора из 4 элементов
void input_vector(float vec[4]) {
    std::cout << "Введите 4 элемента вектора B через пробел:\n";
    for (int i = 0; i < 4; ++i) {
        std::cin >> vec[i];
    }
}

// Функция умножения матрицы на вектор
void multiply_matrix_vector(const float matrix[4][4], const float vec[4], float result[4]) {
    for (int i = 0; i < 4; ++i) {
        float sum = 0.0f; // Аккумулятор для текущей строки
        for (int j = 0; j < 4; ++j) {
            sum += matrix[i][j] * vec[j];
        }
        result[i] = sum;
    }
}

// Функция для вывода результирующего вектора
void print_vector(const float vec[4]) {
    std::cout << "\nРезультирующий вектор C:\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << vec[i] << "\n";
    }
}

int main() {
    float a[4][4];
    float b[4];
    float c[4];

    std::cout << "=== Умножение матрицы на вектор ===\n";

    input_matrix(a);
    input_vector(b);

    multiply_matrix_vector(a, b, c);

    print_vector(c);

    return 0;
}
