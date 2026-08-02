#include <iostream>
#include <cmath>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    float a, b, c;
    std::cout << "Введите коэффициенты a, b, c через пробел: ";
    std::cin >> a >> b >> c;

    // Проверка на квадратное уравнение
    if (a == 0.0f) { 
        std::cout << "Это не квадратное уравнение (a не должно равняться 0)!" << std::endl;
        return 1;
    }

    // Выводим само уравнение для наглядности
    std::cout << "Решаем уравнение: " << a << "x^2";
    if (b >= 0) std::cout << " + " << b << "x";
    else std::cout << " - " << std::abs(b) << "x";
    if (c >= 0) std::cout << " + " << c << " = 0\n";
    else std::cout << " - " << std::abs(c) << " = 0\n";

    // Считаем дискриминант
    float discriminant = b * b - 4.0f * a * c;

    // Сценарий 1: Два корня
    if (discriminant > 0.0f) {
        float x1 = (-b + std::sqrt(discriminant)) / (2.0f * a);
        float x2 = (-b - std::sqrt(discriminant)) / (2.0f * a);
        std::cout << "Корни уравнения x1, x2: " << x1 << ", " << x2 << std::endl;
    }
    // Сценарий 2: Один корень
    else if (discriminant == 0.0f) {
        float x = -b / (2.0f * a);
        std::cout << "Корень уравнения: " << x << std::endl;
    }
    // Сценарий 3: Дискриминант меньше нуля
    else {
        std::cout << "Комплексные числа не поддерживаются!" << std::endl;
    }

    return 0;
}
