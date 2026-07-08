#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int firstNumber = 0;
    int secondNumber = 0;
    int userSum = 0;

    // Описание программы и ввод данных
    std::cout << "=== Тренажёр устного счёта ===\n";
    std::cout << "Введите первое число: ";
    std::cin >> firstNumber;
    std::cout << "Введите второе число: ";
    std::cin >> secondNumber;
    std::cout << "Введите их сумму: ";
    std::cin >> userSum;

    // Программа сама рассчитывает точный результат
    int correctSum = firstNumber + secondNumber;

    std::cout << "-----Проверяем-----\n";

    // Сравниваем ответ пользователя с правильным
    if (userSum == correctSum) {
        std::cout << "Верно!\n";
    } else {
        std::cout << "Ошибка! Верный результат: " << correctSum << "\n";
    }

    return 0;
}
