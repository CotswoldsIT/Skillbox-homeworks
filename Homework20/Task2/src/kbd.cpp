#include <iostream>
#include "kbd.h"
#include "ram.h"

void input() {
    std::cout << "[KBD] Введите 8 целых чисел через пробел: ";
    int value;
    for (int i = 0; i < 8; ++i) {
        std::cin >> value;
        write(i, value); // Запись только через ram.h
    }
}
