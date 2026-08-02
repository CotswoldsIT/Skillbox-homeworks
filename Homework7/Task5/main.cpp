#include <iostream>
#include <cmath> // Библиотека для функции округления std::round

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int kilometers = 0;

    std::cout << "Привет, Сэм! Сколько километров ты сегодня пробежал? ";
    std::cin >> kilometers;

    // Контроль ввода
    if (kilometers <= 0) {
        std::cout << "Ошибка! Количество километров должно быть больше нуля.\n";
        return 1;
    }

    float totalSeconds = 0.0f;

    // Цикл для ввода темпа на каждом километре
    for (int i = 1; i <= kilometers; i++) {
        float pace = 0.0f;
        std::cout << "Какой у тебя был темп на километре " << i << "? ";
        std::cin >> pace;

        if (pace <= 0.0f) {
            std::cout << "Ошибка! Темп должен быть больше нуля. Попробуйте снова.\n";
            i--; // Повторяем ввод для этого же километра
            continue;
        }

        totalSeconds += pace;
    }

    // Считаем средний темп в секундах
    float averagePaceSeconds = totalSeconds / kilometers;

    // Переводим в минуты и секунды
    int minutes = static_cast<int>(averagePaceSeconds) / 60;
    
    // Находим остаток секунд и округляем до ближайшего целого по рекомендации
    int seconds = static_cast<int>(std::round(averagePaceSeconds)) % 60;

    std::cout << "\nВывод:\n";
    std::cout << "Твой средний темп за тренировку: " << minutes << " минуты " << seconds << " секунд.\n";

    return 0;
}
