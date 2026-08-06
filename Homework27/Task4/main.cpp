#include <iostream>
#include <numeric>
#include <limits>
#include <windows.h> 

// Настройка русского языка для Windows консоли (UTF-8)
auto locale_init_in = SetConsoleCP(65001);
auto locale_init_out = SetConsoleOutputCP(65001);

// функция ввода данных в массив фиксированной длины 
template <typename T>
void input(T array[8]) {
    std::cout << "Заполните массив из 8 элементов:\n";
    for (int i = 0; i < 8; ++i) {
        while (true) {
            std::cout << "Элемент [" << i << "]: ";
            if (std::cin >> array[i]) {
                break; // выходим из бесконечного цикла валидации
            } else {
                std::cout << "Ошибка ввода! Пожалуйста, введите корректное число.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

//  функция подсчета среднего арифметического
template <typename T>
double calculateAverage(const T array[8]) {
    double sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += static_cast<double>(array[i]); // Приводим к double для точности
    }
    return sum / 8.0;
}

int main() {
    std::cout << "=== ШАБЛОННЫЙ ПОДСЧЕТ СРЕДНЕГО АРИФМЕТИЧЕСКОГО ===\n\n";

    // Тест 1: Массив целых чисел (int)
    std::cout << "--- ТЕСТ 1: ЦЕЛЫЕ ЧИСЛА (int) ---\n";
    int intArray[8];
    input(intArray);
    std::cout << "Среднее арифметическое (int): " << calculateAverage(intArray) << "\n\n";

    // Тест 2: Массив вещественных чисел (double)
    std::cout << "--- ТЕСТ 2: ВЕЩЕСТВЕННЫЕ ЧИСЛА (double) ---\n";
    double doubleArray[8];
    input(doubleArray);
    std::cout << "Среднее арифметическое (double): " << calculateAverage(doubleArray) << "\n\n";

    std::cout << "Программа успешно завершена.\n";
    return 0;
}
