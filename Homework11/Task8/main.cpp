#include <iostream>
#include <algorithm>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Глобальные массивы полей для двух игроков
bool field_1[10][10] = {false};
bool field_2[10][10] = {false};

// Функция проверки валидности и размещения ОДНОГО корабля
bool place_ship(bool field[10][10], int r1, int c1, int r2, int c2, int size) {
    // Проверка границ поля
    if (r1 < 0 || r1 > 9 || c1 < 0 || c1 > 9 || r2 < 0 || r2 > 9 || c2 < 0 || c2 > 9) {
        std::cout << "Ошибка: Координаты выходят за пределы поля (0-9)!\n";
        return false;
    }

    // Проверка на диагональ
    if (r1 != r2 && c1 != c2) {
        std::cout << "Ошибка: Корабли можно ставить только строго вертикально или горизонтально!\n";
        return false;
    }

    // Нормализуем координаты (чтобы идти от меньшего к большему)
    int start_r = std::min(r1, r2);
    int end_r = std::max(r1, r2);
    int start_c = std::min(c1, c2);
    int end_c = std::max(c1, c2);

    // Проверка длины корабля
    int actual_size = (end_r - start_r) + (end_c - start_c) + 1;
    if (actual_size != size) {
        std::cout << "Ошибка: Неверная длина корабля! Ожидалось клеток: " << size << ", введено: " << actual_size << "\n";
        return false;
    }

    // Проверка на пересечение с другими кораблями
    for (int i = start_r; i <= end_r; ++i) {
        for (int j = start_c; j <= end_c; ++j) {
            if (field[i][j]) {
                std::cout << "Ошибка: В этих клетках уже стоит другой корабль!\n";
                return false;
            }
        }
    }

    // Размещение корабля
    for (int i = start_r; i <= end_r; ++i) {
        for (int j = start_c; j <= end_c; ++j) {
            field[i][j] = true;
        }
    }

    return true;
}

// Обёртка для расстановки всех кораблей одного игрока
void init_player_fleet(bool field[10][10], int player_num) {
    std::cout << "\n=== ИГРОК " << player_num << ": РАССТАНОВКА ФЛОТА ===\n";
    
    // Массив размеров кораблей: 4 однопалубных, 3 двухпалубных, 2 трёхпалубных, 1 четырёхпалубный
    int ship_sizes[] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};
    
    for (int i = 0; i < 10; ++i) {
        int size = ship_sizes[i];
        bool placed = false;
        
        while (!placed) {
            int r1, c1, r2, c2;
            if (size == 1) {
                std::cout << "Введите координаты для однопалубного корабля (ряд и столбец через пробел, 0-9): ";
                std::cin >> r1 >> c1;
                r2 = r1; c2 = c1;
            } else {
                std::cout << "Введите координаты НАЧАЛА и КОНЦА для " << size << "-палубного корабля (ряд1 кол1 ряд2 кол2): ";
                std::cin >> r1 >> c1 >> r2 >> c2;
            }
            
            placed = place_ship(field, r1, c1, r2, c2, size);
            if (!placed) {
                std::cout << "Попробуйте ввести координаты заново.\n";
            }
        }
    }
}

// Функция для совершения выстрела. Возвращает true, если попал
bool make_shot(bool enemy_field[10][10], int r, int c) {
    if (r < 0 || r > 9 || c < 0 || c > 9) {
        std::cout << "Выстрел за молоко! Координаты должны быть от 0 до 9.\n";
        return false;
    }

    if (enemy_field[r][c]) {
        enemy_field[r][c] = false; // Затираем подбитую палубу
        std::cout << "ПОПАЛ!\n";
        return true;
    } else {
        std::cout << "МИМО!\n";
        return false;
    }
}

int main() {
    std::cout << "=== СИМУЛЯТОР МОРСКОГО БОЯ ===\n";

    // Шаг 1: Расстановка кораблей
    init_player_fleet(field_1, 1);
    init_player_fleet(field_2, 2);

    // Счётчики оставшихся палуб у игроков (всего 1*4 + 2*3 + 3*2 + 4*1 = 20 палуб)
    int player1_hp = 20;
    int player2_hp = 20;
    int current_turn = 1;

    std::cout << "\n=== ВСЕ КОРАБЛИ РАССТАВЛЕНЫ! НАЧИНАЕТСЯ БОЙ ===\n";

    // Шаг 2: Игровой цикл битвы
    while (player1_hp > 0 && player2_hp > 0) {
        int r, c;
        std::cout << "\nХод Игрока " << current_turn << ". Введите координаты выстрела (ряд и столбец через пробел, 0-9): ";
        std::cin >> r >> c;

        if (current_turn == 1) {
            if (make_shot(field_2, r, c)) {
                player2_hp--;
            } else {
                current_turn = 2; // Переход хода при промахе
            }
        } else {
            if (make_shot(field_1, r, c)) {
                player1_hp--;
            } else {
                current_turn = 1; // Переход хода при промахе
            }
        }
    }

    // Шаг 3: Объявление победителя
    std::cout << "\n=== ИГРА ОКOНЧЕНА ===\n";
    if (player1_hp == 0) {
        std::cout << "Победил Игрок 2!\n";
    } else {
        std::cout << "Победил Игрок 1!\n";
    }

    return 0;
}
