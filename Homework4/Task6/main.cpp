#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Переменные для текущей даты
    int currentDay = 0, currentMonth = 0, currentYear = 0;
    // Переменные для даты рождения
    int birthDay = 0, birthMonth = 0, birthYear = 0;

    // Текстовый интерфейс: описание и ввод данных
    std::cout << "=== Автоматическая система проверки совершеннолетия ===\n\n";
    
    std::cout << "Введите ТЕКУЩУЮ дату (День Месяц Год) через пробел: ";
    std::cin >> currentDay >> currentMonth >> currentYear;
    
    std::cout << "Введите ДАТУ РОЖДЕНИЯ (День Месяц Год) через пробел: ";
    std::cin >> birthDay >> birthMonth >> birthYear;

    std::cout << "-----Проверяем-----\n";

    // Обработка базового некорректного ввода
    if (currentDay < 1 || currentDay > 31 || currentMonth < 1 || currentMonth > 12 || currentYear < 0 ||
        birthDay < 1 || birthDay > 31 || birthMonth < 1 || birthMonth > 12 || birthYear < 0) {
        std::cout << "Ошибка! Введены некорректные параметры даты.\n";
        return 1;
    }

    // Переводим текущую дату в формат одного большого числа ГГГГММДД
    int currentDateLong = currentYear * 10000 + currentMonth * 100 + currentDay;

    // Сдвигаем год рождения ровно на 18 лет вперед для проверки совершеннолетия
    int targetYear = birthYear + 18;
    int birthDateLongWith18Years = targetYear * 10000 + birthMonth * 100 + birthDay;

    // Согласно ТЗ: в день 18-летия продавать нельзя, а на следующий день - можно.
    // Это значит, что currentDateLong должна быть СТРОГО БОЛЬШЕ, чем дата 18-летия.
    if (currentDateLong > birthDateLongWith18Years) {
        std::cout << "Продавать алкоголь: МОЖНО\n";
    } else {
        std::cout << "Продавать алкоголь: НЕЛЬЗЯ\n";
    }

    return 0;
}
