#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция разворота элементов по указателю согласно чек-листу
void reverse_array(int* arr) {
    for (int i = 0; i < 5; ++i) {
        int temp = arr[i];
        arr[i] = arr[9 - i];
        arr[9 - i] = temp;
    }
}

int main() {
    // Массив из 10 элементов
    int numbers[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "=== Разворот массива через указатель ===\n";
    std::cout << "Исходный массив: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    // Передаем указатель на начало массива в функцию
    reverse_array(numbers);

    std::cout << "Развёрнутый массив: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
