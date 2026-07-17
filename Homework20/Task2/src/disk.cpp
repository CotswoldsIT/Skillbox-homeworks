#include <iostream>
#include <fstream>
#include "disk.h"
#include "ram.h"

void save() {
    std::ofstream file("data.txt");
    if (!file.is_open()) {
        std::cout << "[DISK] Ошибка создания файла data.txt!\n";
        return;
    }
    for (int i = 0; i < 8; ++i) {
        file << read(i) << "\n";
    }
    file.close();
    std::cout << "[DISK] Состояние памяти успешно сохранено в data.txt.\n";
}

void load() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cout << "[DISK] Ошибка: Файл data.txt не найден!\n";
        return;
    }
    int value;
    for (int i = 0; i < 8; ++i) {
        if (file >> value) {
            write(i, value); // Запись только через ram.h
        }
    }
    file.close();
    std::cout << "[DISK] Данные успешно загружены из data.txt в оперативную память.\n";
}
