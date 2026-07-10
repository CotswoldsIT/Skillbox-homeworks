#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int totalLength = 0;
    int exclamationCount = 0;

    std::cout << "Введите общую длину колонтитула: ";
    std::cin >> totalLength;
    std::cout << "Введите количество восклицательных знаков: ";
    std::cin >> exclamationCount;

    // Проверка ввода
    if (totalLength <= 0 || exclamationCount < 0) {
        std::cout << "Ошибка! Размеры должны быть больше нуля.\n";
        return 1;
    }
    if (exclamationCount > totalLength) {
        std::cout << "Ошибка! Знаков не может быть больше, чем вся длина.\n";
        return 1;
    }

    // Считаем сколько волн нужно слева и справа
    int totalWaves = totalLength - exclamationCount;
    int leftWaves = totalWaves / 2;
    int rightWaves = totalWaves - leftWaves; // Остаток пойдет направо, если число нечетное

    // Рисуем левые волны
    for (int i = 0; i < leftWaves; i++) {
        std::cout << "~";
    }

    // Рисуем восклицательные знаки
    for (int i = 0; i < exclamationCount; i++) {
        std::cout << "!";
    }

    // Рисуем правые волны
    for (int i = 0; i < rightWaves; i++) {
        std::cout << "~";
    }

    std::cout << "\n";

    return 0;
}
