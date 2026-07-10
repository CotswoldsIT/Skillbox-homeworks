#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    float startAmplitude = 0.0f;
    float endAmplitude = 0.0f;

    std::cout << "=== Симуляция затухания маятника ===\n";
    std::cout << "Введите начальную амплитуду (см): ";
    std::cin >> startAmplitude;
    std::cout << "Введите конечную амплитуду остановки (см): ";
    std::cin >> endAmplitude;

    // Контроль ввода
    if (startAmplitude <= 0.0f || endAmplitude <= 0.0f) {
        std::cout << "Ошибка! Значения должны быть строго больше нуля.\n";
        return 1;
    }
    if (endAmplitude >= startAmplitude) {
        std::cout << "Маятник уже считается остановившимся: 0 колебаний.\n";
        return 0;
    }

    int swingsCount = 0;
    float currentAmplitude = startAmplitude;

    // Цикл работает, пока маятник качается сильнее, чем граница остановки
    while (currentAmplitude > endAmplitude) {
        // Уменьшаем амплитуду на 8.4% (остается 91.6%)
        currentAmplitude *= 0.916f;
        swingsCount++;
    }

    std::cout << "\nВывод:\n";
    std::cout << "Маятник качнётся " << swingsCount << " раз перед остановкой.\n";

    return 0;
}
