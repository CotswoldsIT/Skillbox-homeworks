#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int experience = 0;

    // Описание программы и ввод данных
    std::cout << "=== Калькулятор уровня персонажа ===\n";
    std::cout << "Введите число очков опыта: ";
    std::cin >> experience;

    std::cout << "-----Считаем-----\n";

    // Проверка на некорректный ввод (отрицательный опыт)
    if (experience < 0) {
        std::cout << "Ошибка! Опыт не может быть отрицательным.\n";
        return 1; // Заверос программы с кодом ошибки
    }

    int level = 1; // Начальный уровень равен 1

    //  Проверка "сверху вниз" без дублирования условий
    if (experience >= 5000) {
        level = 4;
    } else if (experience >= 2500) {
        level = 3;
    } else if (experience >= 1000) {
        level = 2;
    } else {
        level = 1;
    }

    std::cout << "Ваш уровень: " << level << "\n";

    return 0;
}
