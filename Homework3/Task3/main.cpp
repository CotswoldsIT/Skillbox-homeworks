#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int number = 0;

    // Описание программы и ввод данных
    std::cout << "=== Проверка числа на чётность ===\n";
    std::cout << "Введите число: ";
    std::cin >> number;

    std::cout << "-----Проверяем-----\n";

    // Вычисляем остаток от деления на 2
    int remainder = number % 2;

    // Если остаток равен 0 — число чётное
    if (remainder == 0) {
        std::cout << "Число " << number << " — чётное\n";
    } else {
        std::cout << "Число " << number << " — нечётное\n";
    }

    return 0;
}
