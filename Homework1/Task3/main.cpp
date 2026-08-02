#include <iostream>

int main() {
    // Настройка русского языка для консоли
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Исходные данные (имитация ввода данных из примера)
    int shiftDuration = 480;  // Длительность смены в минутах
    int orderTime = 2;        // Время на заказ в минутах
    int deliveryTime = 4;     // Время на сборку заказа в минутах

    // Расчет времени на одного клиента и общего количества обслуженных клиентов
    int timePerClient = orderTime + deliveryTime;
    int clientsServed = shiftDuration / timePerClient;

    // Вывод программы с полной имитацией ввода данных
    std::cout << "Эта программа рассчитает, сколько клиентов успеет обслужить кассир за смену.\n";
    std::cout << "Введите длительность смены в минутах: " << shiftDuration << "\n";
    std::cout << "Сколько минут клиент делает заказ? " << orderTime << "\n";
    std::cout << "Сколько минут кассир собирает заказ? " << deliveryTime << "\n";
    
    std::cout << "-----Считаем-----\n";
    std::cout << "За смену длиной " << shiftDuration << " минут кассир успеет обслужить " 
              << clientsServed << " клиентов.\n";

    return 0;
}
