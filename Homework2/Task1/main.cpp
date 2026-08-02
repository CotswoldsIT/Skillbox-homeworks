#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Постоянная для расчетов
    const int TICKET_PRICE = 20;

    // Переменные для учета пассажиров и финансов
    int currentPassengers = 0;
    int totalTicketsSold = 0;
    int exited = 0;
    int entered = 0;

    // Названия остановок в переменных
    std::string stop1 = "Улица программистов";
    std::string stop2 = "Проспект алгоритмов";
    std::string stop3 = "Площадь циклов";
    std::string stop4 = "Конечная станция";

    // === ОСТАНОВКА 1 ===
    std::cout << "Прибываем на остановку «" << stop1 << "». В салоне пассажиров: " << currentPassengers << "\n\n";
    std::cout << "Сколько пассажиров вышло на остановке? ";
    std::cin >> exited;
    std::cout << "Сколько пассажиров зашло на остановке? ";
    std::cin >> entered;
    
    currentPassengers = currentPassengers - exited + entered;
    totalTicketsSold += entered; // Считаем проданные билеты зашедшим
    
    std::cout << "\nОтправляемся с остановки «" << stop1 << "». В салоне пассажиров: " << currentPassengers << "\n";
    std::cout << "-----------Едем---------\n\n";

    // === ОСТАНОВКА 2 ===
    std::cout << "Прибываем на остановку «" << stop2 << "». В салоне пассажиров: " << currentPassengers << "\n\n";
    std::cout << "Сколько пассажиров вышло на остановке? ";
    std::cin >> exited;
    std::cout << "Сколько пассажиров зашло на остановке? ";
    std::cin >> entered;
    
    currentPassengers = currentPassengers - exited + entered;
    totalTicketsSold += entered;
    
    std::cout << "\nОтправляемся с остановки «" << stop2 << "». В салоне пассажиров: " << currentPassengers << "\n";
    std::cout << "-----------Едем---------\n\n";

    // === ОСТАНОВКА 3 ===
    std::cout << "Прибываем на остановку «" << stop3 << "». В салоне пассажиров: " << currentPassengers << "\n\n";
    std::cout << "Сколько пассажиров вышло на остановке? ";
    std::cin >> exited;
    std::cout << "Сколько пассажиров зашло на остановке? ";
    std::cin >> entered;
    
    currentPassengers = currentPassengers - exited + entered;
    totalTicketsSold += entered;
    
    std::cout << "\nОтправляемся с остановки «" << stop3 << "». В салоне пассажиров: " << currentPassengers << "\n";
    std::cout << "-----------Едем---------\n\n";

    // === ОСТАНОВКА 4 (Финальная) ===
    std::cout << "Прибываем на остановку «" << stop4 << "». В салоне пассажиров: " << currentPassengers << "\n\n";
    std::cout << "Сколько пассажиров вышло на остановке? ";
    std::cin >> exited;
    std::cout << "Сколько пассажиров зашло на остановке? ";
    std::cin >> entered;
    
    currentPassengers = currentPassengers - exited + entered;
    totalTicketsSold += entered;
    
    std::cout << "\nКонечная остановка «" << stop4 << "». Автобус завершил маршрут.\n";
    std::cout << "------------------------------------\n\n";

    // === РАСЧЕТ ДОХОДОВ И РАСХОДОВ ===
    int totalEarned = totalTicketsSold * TICKET_PRICE;
    int driverSalary = totalEarned / 4;       // Четверть (1/4)
    int fuelExpenses = totalEarned / 5;       // Пятая часть (1/5)
    int taxes = totalEarned / 5;              // Пятая часть (1/5)
    int repairExpenses = totalEarned / 5;     // Пятая часть (1/5)
    
    // Чистый доход (вычитаем все расходы)
    int netProfit = totalEarned - driverSalary - fuelExpenses - taxes - repairExpenses;

    // Вывод финансового отчета строго по ТЗ
    std::cout << "Всего заработали: " << totalEarned << " руб.\n\n";
    std::cout << "Зарплата водителя: " << driverSalary << " руб.\n\n";
    std::cout << "Расходы на топливо: " << fuelExpenses << " руб.\n\n";
    std::cout << "Налоги: " << taxes << " руб.\n\n";
    std::cout << "Расходы на ремонт машины: " << repairExpenses << " руб.\n\n";
    std::cout << "Итого доход: " << netProfit << " руб.\n";

    return 0;
}
