#include <iostream>
#include <cmath> // Библиотека для функции std::pow

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Переменные с плавающей точкой
    float force = 0.0f;
    float mass = 0.0f;
    float time = 0.0f;

    std::cout << "=== Симулятор космических полетов ===\n";
    std::cout << "Введите силу тяги двигателя (Н): ";
    std::cin >> force;
    std::cout << "Введите массу звездолета (кг): ";
    std::cin >> mass;
    std::cout << "Введите время работы двигателя (с): ";
    std::cin >> time;

    // Проверка ввода
    if (force < 0.0f || mass <= 0.0f || time < 0.0f) {
        std::cout << "Ошибка! Некорректные значения (масса должна быть строго больше нуля).\n";
        return 1;
    }

    // Расчет ускорения: a = F / m
    float acceleration = force / mass;

    // Расчет расстояния: S = (a * t^2) / 2
    float distance = (acceleration * std::pow(time, 2)) / 2.0f;

    std::cout << "Через " << time << " с корабль переместится на " << distance << " метров.\n";

    return 0;
}
