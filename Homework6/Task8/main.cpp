#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int height = 0;

    std::cout << "Введите высоту елочки: ";
    std::cin >> height;

    // Контроль ввода
    if (height <= 0) {
        std::cout << "Ошибка! Высота должна быть больше нуля.\n";
        return 1;
    }

    // высота ёлочки
    for (int i = 1; i <= height; i++) {
        
        // Цикл для вывода пробелов слева
        for (int j = 0; j < height - i; j++) {
            std::cout << " ";
        }

        // Цикл для вывода решёток
        for (int j = 0; j < 2 * i - 1; j++) {
            std::cout << "#";
        }

        // Перенос строки в конце каждого ряда
        std::cout << "\n";
    }

    return 0;
}
