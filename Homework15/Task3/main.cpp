#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    // Открываем файл ведомости для чтения
    std::ifstream file("statement.txt");

    // Контроль открытия файла
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл statement.txt!\n";
        return 1;
    }

    std::cout << "=== Анализ ведомости выплат ===\n";

    std::string first_name, last_name, date;
    int money = 0;
    
    int total_sum = 0;
    int max_money = -1;
    std::string max_payout_person = "";

    // Пошагово считываем разные типы данных из текстового файла
    while (file >> first_name >> last_name >> money >> date) {
        total_sum += money; // Суммируем общие выплаты

        // Ищем человека с максимальной суммой выплат
        if (money > max_money) {
            max_money = money;
            max_payout_person = first_name + " " + last_name;
        }
    }

    file.close();

    // Выводим результаты анализа 
    std::cout << "Общая сумма выплаченных средств: " << total_sum << "\n";
    std::cout << "Самый крупный получатель: " << max_payout_person << " (Сумма: " << max_money << ")\n";

    return 0;
}
