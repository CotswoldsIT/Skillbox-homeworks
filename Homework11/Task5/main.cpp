#include <iostream>
#include <algorithm>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция инициализации пупырки (все пузырьки целые)
void init_bubble_wrap(bool wrap[12][12]) {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            wrap[i][j] = true;
        }
    }
}

// Функция отображения пупырки. Возвращает true, если остались целые пузырьки
bool print_bubble_wrap(const bool wrap[12][12]) {
    bool has_intact = false;
    std::cout << "\nТекущее состояние пупырки:\n";
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (wrap[i][j]) {
                std::cout << "o ";
                has_intact = true; // Нашли хотя бы один целый
            } else {
                std::cout << "x ";
            }
        }
        std::cout << "\n";
    }
    return has_intact;
}

// Функция лопания региона пузырьков
void pop_region(bool wrap[12][12], int r1, int c1, int r2, int c2) {
    // Корректируем порядок координат (на случай, если ввели наоборот)
    int start_r = std::min(r1, r2);
    int end_r = std::max(r1, r2);
    int start_c = std::min(c1, c2);
    int end_c = std::max(c1, c2);

    // Лопаем пузырьки в указанном регионе
    for (int i = start_r; i <= end_r; ++i) {
        for (int j = start_c; j <= end_c; ++j) {
            if (wrap[i][j]) {
                wrap[i][j] = false;
                std::cout << "Pop!\n";
            }
        }
    }
}

int main() {
    bool wrap[12][12];
    init_bubble_wrap(wrap);

    std::cout << "=== Симулятор пупырки (12х12) ===\n";

    // Играем, пока функция отображения возвращает true (есть целые пузырьки)
    while (print_bubble_wrap(wrap)) {
        int r1, c1, r2, c2;
        std::cout << "\nВведите координаты региона для лопания.\n";
        std::cout << "Начало (ряд и столбец от 1 до 12): ";
        std::cin >> r1 >> c1;
        std::cout << "Конец (ряд и столбец от 1 до 12): ";
        std::cin >> r2 >> c2;

        // Контроль ввода: валидация диапазона значений
        if (r1 < 1 || r1 > 12 || c1 < 1 || c1 > 12 || 
            r2 < 1 || r2 > 12 || c2 < 1 || c2 > 12) {
            std::cout << "Ошибка! Координаты должны быть строго в диапазоне от 1 до 12.\n";
            continue;
        }

        // Переводим координаты в индексы массива (0-11)
        pop_region(wrap, r1 - 1, c1 - 1, r2 - 1, c2 - 1);
    }

    std::cout << "\nУра! Вся пупырка лопнута. Игра завершена!\n";
    return 0;
}
