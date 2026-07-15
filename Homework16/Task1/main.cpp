#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция валидации даты ДД.ММ.ГГГГ 
bool is_valid_date(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '.' || date[5] != '.') return false;

    try {
        int day = std::stoi(date.substr(0, 2));
        int month = std::stoi(date.substr(3, 2));
        int year = std::stoi(date.substr(6, 4));

        if (day < 1 || day > 31) return false;
        if (month < 1 || month > 12) return false;
        if (year < 1900 || year > 2100) return false;
    } catch (...) {
        return false; // Если stoi выбросит исключение при неверных символах
    }

    return true;
}

int main() {
    std::string first_name, last_name, date;
    int money;

    std::cout << "=== Запись в ведомость учёта выплат ===\n";
    
    std::cout << "Введите имя: ";
    std::cin >> first_name;
    std::cout << "Введите фамилию: ";
    std::cin >> last_name;
    
    std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
    std::cin >> date;
    if (!is_valid_date(date)) {
        std::cout << "Ошибка: Неверный формат даты!\n";
        return 1;
    }

    std::cout << "Введите сумму выплаты (в рублях): ";
    std::cin >> money;
    if (money < 0) {
        std::cout << "Ошибка: Сумма не может быть отрицательной!\n";
        return 1;
    }

    // Открываем файл в режиме добавления (ios::app) 
    std::ofstream file("statement.txt", std::ios::app);

    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл для записи!\n";
        return 1;
    }

    // Записываем разные типы данных в файл через пробел с переносом строки в конце
    file << first_name << " " << last_name << " " << date << " " << money << "\n";
    file.close();

    std::cout << "Запись успешно добавлена в ведомость statement.txt!\n";

    return 0;
}
