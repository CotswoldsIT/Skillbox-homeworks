#include <iostream>
#include <string>
#include "ram.h"
#include "cpu.h"
#include "disk.h"
#include "gpu.h"
#include "kbd.h"

auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::cout << "=== Симулятор работы персонального компьютера ===\n";
    std::cout << "Доступные команды: input, display, sum, save, load, exit\n\n";

    std::string command;
    while (true) {
        std::cout << "\nВведите команду: ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Завершение работы симулятора.\n";
            break;
        }
        else if (command == "input") {
            input();
        }
        else if (command == "display") {
            display();
        }
        else if (command == "sum") {
            compute();
        }
        else if (command == "save") {
            save();
        }
        else if (command == "load") {
            load();
        }
        else {
            std::cout << "Ошибка: Неизвестная команда. Повторите ввод.\n";
        }
    }

    return 0;
}
