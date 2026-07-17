#include <iostream>
#include "gpu.h"
#include "ram.h"

void display() {
    std::cout << "[GPU] Текущее содержимое памяти: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << read(i) << " ";
    }
    std::cout << "\n";
}
