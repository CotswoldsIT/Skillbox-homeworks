#include <iostream>
#include <cmath> // Библиотека для функции std::abs (модуль числа)

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    long long number = 0; // Используем long long для поддержки очень больших чисел

    // Текстовый интерфейс: описание и ввод данных
    std::cout << "=== Калькулятор количества цифр в числе ===\n";
    std::cout << "Введите число: ";
    std::cin >> number;

    // Избавляемся от знака минус для отрицательных чисел
    long long tempNumber = std::abs(number);

    int digitCount = 0;

    // Цикл do while гарантирует, что даже для числа 0 выполнится один шаг.
    // Если использовать цикл while (number > 0), то для нуля он не начнется и выдаст 0 цифр.
    do {
        digitCount++;
        tempNumber /= 10; // Отрезаем последнюю цифру
    } while (tempNumber > 0);

    // Вывод результата
    std::cout << "Цифр в числе " << number << ": " << digitCount << "\n";

    return 0;
}
