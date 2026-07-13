#include <iostream>

// Настройка русского языка 
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция для ввода матрицы 4x4 с клавиатуры
void input_matrix(int matrix[4][4], char name) {
    std::cout << "Введите элементы матрицы " << name << " (16 чисел через пробел или Enter):\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

// Функция для красивого вывода матрицы в консоль
void print_matrix(int matrix[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

// ОПТИМАЛЬНОЕ СРАВНЕНИЕ: возвращает false при первом же несовпадении
bool are_matrices_equal(int a[4][4], int b[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (a[i][j] != b[i][j]) {
                return false; 
            }
        }
    }
    return true;
}

// Преобразование матрицы в диагональный вид "на месте"
void make_diagonal(int matrix[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j) {
                matrix[i][j] = 0; // Зануляем всё вне главной диагонали
            }
        }
    }
}

int main() {
    int A[4][4];
    int B[4][4];

    std::cout << "=== Сравнение и преобразование матриц 4x4 ===\n";
    
    // Ввод двух матриц
    input_matrix(A, 'A');
    input_matrix(B, 'B');

    // Сравнение матриц
    if (!are_matrices_equal(A, B)) {
        std::cout << "\nМатрицы не равны. Выполнение программы прекращено.\n";
        return 0; 
    }

    std::cout << "\nМатрицы равны!\n";

    // Преобразование первой матрицы в диагональный вид и вывод результата
    make_diagonal(A);

    std::cout << "\nРезультат приведения матрицы к диагональному виду:\n";
    print_matrix(A);

    return 0;
}
