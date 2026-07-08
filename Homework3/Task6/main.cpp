#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Исходные данные
    int totalPeople = 0;   // Всего людей в городе
    int totalBarbers = 0;  // Всего барберов в городе

    // Константы из условий задачи
    const int WORK_DAYS_PER_MONTH = 30; // Дней в месяце
    const int HOURS_PER_DAY = 8;        // Рабочих часов в день
    const int TIME_PER_CLIENT = 1;      // Часов на одного клиента

    // Описание программы и ввод данных
    std::cout << "=== Расчёт достаточности барберов в городе ===\n";
    std::cout << "Введите численность населения города: ";
    std::cin >> totalPeople;
    std::cout << "Введите текущее количество барберов: ";
    std::cin >> totalBarbers;

    std::cout << "-----Считаем-----\n";

    // Защита от деления на ноль (если барберов нет вообще)
    if (totalBarbers <= 0) {
        std::cout << "В городе нет барберов! Нужно срочно нанять персонал.\n";
        return 0;
    }

    // 1. Сколько клиентов может обслужить ОДИН барбер за месяц
    int clientsPerBarber = (HOURS_PER_DAY / TIME_PER_CLIENT) * WORK_DAYS_PER_MONTH;

    // 2. Вычисляем, сколько ВСЕГО барберов нужно городу (целочисленное деление)
    int requiredBarbers = totalPeople / clientsPerBarber;

    // 3. Используем оператор %, чтобы проверить, остались ли "лишние" люди
    if (totalPeople % clientsPerBarber > 0) {
        requiredBarbers += 1; // Если остался хотя бы один человек, нужен еще +1 барбер
    }

    // 4. Сравниваем, хватает ли текущих барберов
    std::cout << "Для обслуживания города необходимо барберов: " << requiredBarbers << "\n";
    std::cout << "У вас в наличии: " << totalBarbers << "\n\n";

    if (totalBarbers >= requiredBarbers) {
        std::cout << "Барберов хватает! Город будет подстрижен.\n";
    } else {
        std::cout << "Барберов НЕ хватает! Нужно нанять ещё как минимум " 
                  << (requiredBarbers - totalBarbers) << " сотр.\n";
    }

    return 0;
}
