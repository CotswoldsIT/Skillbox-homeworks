#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    float health = 0.0f;
    float resistance = 0.0f;

    std::cout << "=== Симулятор боя с орком ===\n";
    std::cout << "Введите здоровье орка (от 0 до 1): ";
    std::cin >> health;
    std::cout << "Введите сопротивляемость магии (от 0 до 1): ";
    std::cin >> resistance;

    // Проверка начального ввода
    if (health <= 0.0f || health > 1.0f || resistance < 0.0f || resistance > 1.0f) {
        std::cout << "Ошибка! Неверные параметры орка.\n";
        return 1;
    }

    // Цикл выстрелов, пока орк жив
    while (health > 0.0f) {
        float power = 0.0f;
        std::cout << "\nВведите мощность огненного шара (от 0 до 1): ";
        std::cin >> power;

        // Проверка ввода мощности
        if (power < 0.0f || power > 1.0f) {
            std::cout << "Ошибка! Мощность должна быть от 0 до 1. Попробуйте снова.\n";
            continue;
        }

        // Считаем урон с учетом сопротивляемости
        float damage = power * (1.0f - resistance);
        health -= damage;

        // Если здоровье ушло в минус, приравниваем к нулю
        if (health < 0.0f) {
            health = 0.0f;
        }

        std::cout << "Нанесено урона: " << damage << "\n";
        std::cout << "Осталось здоровья: " << health << "\n";
    }

    std::cout << "\nОрк погиб. Сражение окончено!\n";

    return 0;
}
