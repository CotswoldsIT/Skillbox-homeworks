#include <iostream>

// Функция для отрисовки игрового поля
void print_board(char board[3][3]) {
    std::cout << "\n  1 2 3\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "  -----\n";
    }
    std::cout << "\n";
}

// Функция проверки победы (только по горизонтали и вертикали по ТЗ)
bool check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        // Проверка строк (горизонтали)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        // Проверка столбцов (вертикали)
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    return false;
}

int main() {
    // Настройка русского языка в консоли
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Инициализация поля пробелами
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char current_player = 'X';
    int total_turns = 0;
    bool game_over = false;

    std::cout << "=== Игра Крестики-Нолики (3х3) ===\n";
    print_board(board);

    // Игровой цикл ограничен 9 ходами
    while (total_turns < 9 && !game_over) {
        int row, col;
        std::cout << "Игрок " << current_player << ", введите координаты (ряд и столбец от 1 до 3) через пробел: ";
        std::cin >> row >> col;

        // Контроль ввода: проверка выхода за границы
        if (row < 1 || row > 3 || col < 1 || col > 3) {
            std::cout << "Ошибка! Координаты должны быть от 1 до 3. Попробуйте еще раз.\n";
            continue; 
        }

        // Переводим в индексы массива (0-2)
        int r = row - 1;
        int c = col - 1;

        // Контроль ввода: проверка занятости клетки
        if (board[r][c] != ' ') {
            std::cout << "Ошибка! Клетка [" << row << "][" << col << "] уже занята. Попробуйте еще раз.\n";
            continue;
        }

        // Делаем ход
        board[r][c] = current_player;
        total_turns++;
        print_board(board);

        // Проверяем на победу
        if (check_win(board, current_player)) {
            std::cout << "Поздравляем! Игрок " << current_player << " победил!\n";
            game_over = true;
            break;
        }

        // Смена игрока
        if (current_player == 'X') {
            current_player = 'O';
        } else {
            current_player = 'X';
        }
    }

    // Если ходы кончились, а победителя нет
    if (!game_over && total_turns == 9) {
        std::cout << "Ничья! Свободных клеток не осталось.\n";
    }

    return 0;
}
