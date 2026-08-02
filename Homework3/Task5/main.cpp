#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int firstNumber = 0;
    int secondNumber = 0;

    // Описание программы и ввод данных
    std::cout << "=== Проверка кратности чисел ===\n";
    std::cout << "Введите первое число: ";
    std::cin >> firstNumber;
    std::cout << "Введите второе число: ";
    std::cin >> secondNumber;

    std::cout << "-----Проверяем-----\n";

    // Защита от деления на ноль
    if (secondNumber == 0) {
        std::cout << "Ошибка! Делить на ноль нельзя.\n";
        return 1; // Завершаем программу с кодом ошибки
    }

    // Проверяем остаток от деления
    if (firstNumber % secondNumber == 0) {
        std::cout << "Да, " << firstNumber << " делится на " << secondNumber << " без остатка!\n";
    } else {
        std::cout << "Нет, " << firstNumber << " не делится на " << secondNumber << " без остатка!\n";
    }

    return 0;
}
