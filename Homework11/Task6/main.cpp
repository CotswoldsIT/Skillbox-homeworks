#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция вывода двумерного массива на экран
void print_snake_matrix(const int matrix[5][5]) {
    std::cout << "\nРезультат вывода матрицы змейкой:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    int digits[5][5];
    int number = 0;

    std::cout << "=== Заполнение матрицы змейкой без условных операторов ===\n";

    // Инициализация матрицы 
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            //  формула переключения направления столбца на основе чётности строки
            int col = j * (1 - i % 2) + (4 - j) * (i % 2);
            digits[i][col] = number;
            number += 1;
        }
    }

    print_snake_matrix(digits);

    return 0;
}
