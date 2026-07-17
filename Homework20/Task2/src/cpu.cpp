#include <iostream>
#include "cpu.h"
#include "ram.h"

void compute() {
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += read(i); // Чтение только через ram.h
    }
    std::cout << "[CPU] Сумма элементов в памяти: " << sum << "\n";
}
