#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int firstNumber = 0;
    int secondNumber = 0;

    // Описание программы и ввод данных
    std::cout << "=== Поиск минимального из двух чисел ===\n";
    std::cout << "Введите первое число: ";
    std::cin >> firstNumber;
    std::cout << "Введите второе число: ";
    std::cin >> secondNumber;

    std::cout << "-----Проверяем-----\n";

    // Условная конструкция для проверки всех вариантов
    if (firstNumber < secondNumber) {
        std::cout << "Наименьшее число: " << firstNumber << "\n";
    } 
    else if (secondNumber < firstNumber) {
        std::cout << "Наименьшее число: " << secondNumber << "\n";
    } 
    else {
        std::cout << "Числа равны!\n";
    }

    return 0;
}

