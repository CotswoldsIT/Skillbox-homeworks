#include <iostream>
#include <cstdio> // Необходимо для работы функции sprintf/snprintf

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    float speed = 0.0f;
    float delta = 0.0f;
    char speed_str[100]; // Отдельная строка-буфер для спидометра

    // Игровой/рабочий цикл do...while 
    do {
        std::cout << "Введите изменение скорости: ";
        std::cin >> delta;

        // Изменяем скорость на величину дельты
        speed += delta;

        // Контроль диапазона: скорость не может быть выше 150 км/ч
        if (speed > 150.0f) {
            speed = 150.0f;
        }
        
        // Контроль диапазона: скорость не может быть меньше 0 км/ч
        if (speed < 0.0f) {
            speed = 0.0f;
        }

        // Форматируем вывод в строку-буфер с точностью до 0.1
        std::snprintf(speed_str, sizeof(speed_str), "Текущая скорость: %.1f км/ч", speed);
        std::cout << speed_str << "\n";

        // Цикл работает, пока скорость строго больше нуля с дельтой 0.01
    } while (speed > 0.01f);

    std::cout << "Машина полностью остановилась. Программа завершена.\n";

    return 0;
}
