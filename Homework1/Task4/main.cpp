#include <iostream>

int main() {
    // Настройка русского языка для консоли
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Bмитация ввода данных из примера
    int totalBill = 4000000;      // Сумма в квитанции
    int entranceCount = 10;       // Количество подъездов
    int apartmentsPerEntrance = 40; // Квартир в каждом подъезде

    // Расчет общего количества квартир и суммы на одну квартиру
    int totalApartments = entranceCount * apartmentsPerEntrance;
    int billPerApartment = totalBill / totalApartments;

    // Вывод программы с имитацией ввода данных
    std::cout << "Калькулятор квартплаты\n\n";
    std::cout << "Введите сумму, указанную в квитанции: " << totalBill << "\n";
    std::cout << "Сколько подъездов в вашем доме? " << entranceCount << "\n";
    std::cout << "Сколько квартир в каждом подъезде? " << apartmentsPerEntrance << "\n";
    
    std::cout << "----Считаем-----\n";
    std::cout << "Каждая квартира должна платить по " << billPerApartment << " руб.\n";

    return 0;
}
