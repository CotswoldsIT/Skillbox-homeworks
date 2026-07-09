#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int ticketNumber = 0;

    // Текстовый интерфейс: описание и ввод данных
    std::cout << "=== Проверка счастливого билета ===\n";
    std::cout << "Введите шестизначный номер билета: ";
    std::cin >> ticketNumber;

    // Контроль ввода (номер билета должен быть шестизначным)
    if (ticketNumber < 100000 || ticketNumber > 999999) {
        std::cout << "Ошибка! Номер билета должен состоять строго из 6 цифр.\n";
        return 1;
    }

    int firstHalfSum = 0;
    int secondHalfSum = 0;
    int tempNumber = ticketNumber;

    // Цикл выполняется 3 раза (обрабатывает по 2 цифры за раз: одну для первой половины, одну для второй)
    int steps = 3; 
    while (steps > 0) {
        // Забираем цифру для второй (правой) половины билета
        secondHalfSum += tempNumber % 10;
        tempNumber /= 10;

        // Забираем цифру для первой (левой) половины билета
        firstHalfSum += tempNumber % 10;
        tempNumber /= 10;

        steps--;
    }

    std::cout << "-----Проверяем-----\n";

    // Сравниваем суммы половин билета
    if (firstHalfSum == secondHalfSum) {
        std::cout << "Билет счастливый!\n";
    } else {
        std::cout << "Повезёт в следующий раз!\n";
    }

    return 0;
}
