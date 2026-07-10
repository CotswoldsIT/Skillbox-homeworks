#include <iostream>

int main() {
    // Настройка русского языка для вывода текста
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Исходные запасы ингредиентов
    int water = -1;
    int milk = -1;

    // Ввод количества воды с контролем ввода
    while (water < 0) {
        std::cout << "Введите количество воды в мл: ";
        std::cin >> water;
        if (water < 0) {
            std::cout << "Ошибка! Количество должно быть неотрицательным цифрой.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    // Ввод количества молока с контролем ввода
    while (milk < 0) {
        std::cout << "Введите количество молока в мл: ";
        std::cin >> milk;
        if (milk < 0) {
            std::cout << "Ошибка! Количество должно быть неотрицательным цифрой.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    // Счетчики приготовленных напитков
    int americanoCount = 0;
    int latteCount = 0;

    // Флаг для выхода из цикла, если ингредиенты подошли к концу
    bool machineRunning = true;

    // Цикл работает, пока машина активна и хватает ингредиентов хотя бы на один напиток
    while (machineRunning && (water >= 300 || (water >= 30 && milk >= 270))) {
        int choice = -1;

        // Выбор напитка с контролем ввода
        while (choice != 1 && choice != 2) {
            std::cout << "Выберите напиток (1 — американо, 2 — латте): ";
            std::cin >> choice;
            if (choice != 1 && choice != 2) {
                std::cout << "Ошибка! Выберите 1 или 2.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }

        // Логика приготовления
        if (choice == 1) {
            if (water >= 300) {
                water -= 300;
                americanoCount++;
                std::cout << "Ваш напиток готов.\n";
            } else {
                std::cout << "Не хватает воды.\n";
                machineRunning = false; // Прерываем работу, ингредиенты кончились
            }
        } else if (choice == 2) {
            if (water >= 30 && milk >= 270) {
                water -= 30;
                milk -= 270;
                latteCount++;
                std::cout << "Ваш напиток готов.\n";
            } else if (water < 30) {
                std::cout << "Не хватает воды.\n";
                machineRunning = false;
            } else {
                std::cout << "Не хватает молока.\n";
                machineRunning = false;
            }
        }
        std::cout << "\n";
    }

    // Вывод итогового отчета, когда ингредиенты закончились
    std::cout << "***Отчёт***\n";
    std::cout << "Ингредиентов осталось:\n";
    std::cout << "            Вода: " << water << " мл\n";
    std::cout << "            Молоко: " << milk << " мл\n";
    std::cout << "Кружек американо приготовлено: " << americanoCount << "\n";
    std::cout << "Кружек латте приготовлено: " << latteCount << "\n";

    return 0;
}
