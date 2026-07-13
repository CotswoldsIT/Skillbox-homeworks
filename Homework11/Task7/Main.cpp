#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция заполнения на основе двумерной матрицы высот
void generate_world(bool world[5][5][10]) {
    std::cout << "Введите высоты ландшафта (матрица 5x5, числа от 0 до 10):\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            int height;
            std::cin >> height;

            // Ограничение ввода высоты от 0 до 10 блоков
            if (height < 0) height = 0;
            if (height > 10) height = 10;

            // Заполняем трехмерный массив блоками земли (true) до указанной высоты
            for (int h = 0; h < 10; ++h) {
                if (h < height) {
                    world[i][j][h] = true;
                } else {
                    world[i][j][h] = false;
                }
            }
        }
    }
}

// Функция вывода горизонтального среза на определенной высоте
void print_slice(const bool world[5][5][10], int level) {
    std::cout << "\nГоризонтальный срез на уровне " << level << ":\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (world[i][j][level]) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    // Создаем трехмерный мир размером 5х5 и высотой 10 уровней
    bool world[5][5][10];

    std::cout << "=== Симулятор ландшафта Почти Майнкрафт ===\n";

    generate_world(world);

    int level;
    std::cout << "\nВведите уровень горизонтального среза для отображения (от 0 до 9): ";
    std::cin >> level;

    // Контроль ввода уровня среза
    if (level < 0 || level > 9) {
        std::cout << "Ошибка! Уровень среза должен быть в диапазоне от 0 до 9.\n";
        return 0;
    }

    print_slice(world, level);

    return 0;
}
