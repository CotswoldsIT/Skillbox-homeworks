#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

const int MAX_BILLS = 1000;
const int NOMINALS[] = {100, 200, 500, 1000, 2000, 5000};
const int NOMINALS_COUNT = 6;

// Функция для вывода баланса и количества купюр
void show_status(const int bank[]) {
    int counts[NOMINALS_COUNT] = {0};
    int total_sum = 0;
    int total_bills = 0;

    for (int i = 0; i < MAX_BILLS; ++i) {
        if (bank[i] > 0) {
            total_sum += bank[i];
            total_bills++;
            for (int j = 0; j < NOMINALS_COUNT; ++j) {
                if (bank[i] == NOMINALS[j]) {
                    counts[j]++;
                    break;
                }
            }
        }
    }

    std::cout << "\n--- ТЕКУЩЕЕ СОСТОЯНИЕ БАНКОМАТА ---\n";
    for (int j = 0; j < NOMINALS_COUNT; ++j) {
        std::cout << NOMINALS[j] << " руб.: " << counts[j] << " шт.\n";
    }
    std::cout << "Всего купюр в банкомате: " << total_bills << " из " << MAX_BILLS << "\n";
    std::cout << "Общая сумма в банкомате: " << total_sum << " руб.\n";
    std::cout << "-----------------------------------\n";
}

// Функция сохранения состояния в бинарный файл
void save_bank(const int bank[]) {
    std::ofstream file("atm.bin", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(bank), sizeof(int) * MAX_BILLS);
        file.close();
    }
}

int main() {
    std::srand(std::time(nullptr));
    int bank[MAX_BILLS] = {0};

    // Загрузка данных из бинарного файла при старте
    std::ifstream file("atm.bin", std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(bank), sizeof(int) * MAX_BILLS);
        file.close();
        std::cout << "Данные банкомата успешно загружены.\n";
        show_status(bank);
    } else {
        std::cout << "Банкомат пуст (файл данных не найден).\n";
    }

    std::string command;
    while (true) {
        std::cout << "\nВведите команду (+ для инкассации, - для снятия, exit для выхода): ";
        std::cin >> command;

        if (command == "exit") {
            save_bank(bank);
            std::cout << "Состояние сохранено. Завершение работы.\n";
            break;
        }

        if (command == "+") {
            // Заполнение недостающих купюр случайным образом
            for (int i = 0; i < MAX_BILLS; ++i) {
                if (bank[i] == 0) {
                    bank[i] = NOMINALS[std::rand() % NOMINALS_COUNT];
                }
            }
            std::cout << "Банкомат полностью заполнен инкассаторами.\n";
            show_status(bank);
            save_bank(bank);
        } 
        else if (command == "-") {
            int amount;
            std::cout << "Введите сумму для снятия (кратную 100): ";
            std::cin >> amount;

            if (amount <= 0 || amount % 100 != 0) {
                std::cout << "Ошибка: Сумма должна быть больше нуля и кратна 100 рублям.\n";
                continue;
            }

            int temp_amount = amount;
            // Массив индексов купюр, которые мы планируем выдать
            int bills_to_give[MAX_BILLS];
            int to_give_count = 0;

            // Жадный алгоритм выдачи денег начиная с крупных номиналов
            for (int j = NOMINALS_COUNT - 1; j >= 0; --j) {
                int current_nominal = NOMINALS[j];
                
                // Ищем купюры текущего номинала в банкомате
                for (int i = 0; i < MAX_BILLS; ++i) {
                    if (bank[i] == current_nominal && temp_amount >= current_nominal) {
                        temp_amount -= current_nominal;
                        bills_to_give[to_give_count++] = i; // Запоминаем индекс купюры
                    }
                }
            }

            // Проверяем, удалось ли набрать всю сумму
            if (temp_amount == 0) {
                // Сумма набрана, удаляем эти купюры из банкомата (зануляем ячейки)
                for (int i = 0; i < to_give_count; ++i) {
                    bank[bills_to_give[i]] = 0;
                }
                std::cout << "Успешно! Выдано " << amount << " руб.\n";
                show_status(bank);
                save_bank(bank);
            } else {
                std::cout << "Операция невозможна: в банкомате недостаточно подходящих купюр.\n";
            }
        } 
        else {
            std::cout << "Неизвестная команда. Повторите ввод.\n";
        }
    }

    return 0;
}
