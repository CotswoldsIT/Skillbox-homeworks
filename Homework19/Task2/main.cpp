#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

struct Friend {
    std::string name;
    std::tm birthday; // Структура даты рождения 
};

int main() {
    // Получаем текущее системное время
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::vector<Friend> friends;
    std::cout << "=== Программа напоминания о днях рождения ===\n";
    std::cout << "Вводите данные. Формат ввода даты: ДД.ММ.ГГГГ (например, 17.07.1995)\n";
    std::cout << "Для окончания ввода введите 'end' вместо имени.\n\n";

    while (true) {
        std::string name;
        std::cout << "Имя друга: ";
        std::cin >> name;

        if (name == "end") {
            break;
        }

        std::string date_str;
        std::cout << "Дата рождения (ДД.ММ.ГГГГ): ";
        std::cin >> date_str;

        // Валидация нового формата ДД.ММ.ГГГГ
       if (date_str.length() != 10 || date_str[2] != '.' || date_str[5] != '.') {
            std::cout << "Ошибка: Неверный формат даты! Используйте ДД.ММ.ГГГГ.\n";
            continue;
        }

        try {
            Friend f;
            f.name = name;
            f.birthday = {}; 
            
            // Парсим строку ДД.ММ.ГГГГ по новым индексам
            int day = std::stoi(date_str.substr(0, 2));
            int month = std::stoi(date_str.substr(3, 2));
            int year = std::stoi(date_str.substr(6, 4));

            f.birthday.tm_year = year - 1900;
            f.birthday.tm_mon = month - 1; // Месяцы в tm идут от 0 до 11
            f.birthday.tm_mday = day;

            friends.push_back(f);
        } catch (...) {
            std::cout << "Ошибка парсинга даты. Попробуйте снова.\n";
        }
    }

    std::cout << "\n--- АНАЛИЗ ДНЕЙ РОЖДЕНИЯ ---\n";
    
    bool celebrate_today = false;
    std::vector<Friend> future_birthdays;
    int min_days_left = 366;

    for (const auto& f : friends) {
        // Проверка: день рождения сегодня?
        if (f.birthday.tm_mon == now->tm_mon && f.birthday.tm_mday == now->tm_mday) {
            std::cout << "🎉 Сегодня день рождения у друга: " << f.name << "!\n";
            celebrate_today = true;
            continue;
        }

        // Переносим день рождения на текущий год для расчета разницы дней
        std::tm b_this_year = f.birthday;
        b_this_year.tm_year = now->tm_year;
        
        std::time_t b_time = std::mktime(&b_this_year);
        double seconds_left = std::difftime(b_time, t);
        
        // Если день рождения в этом году уже прошел — пропускаем 
        if (seconds_left < 0) {
            continue; 
        }

        int days_left = static_cast<int>(seconds_left / 86400);
        if (days_left < min_days_left) {
            min_days_left = days_left;
        }
        future_birthdays.push_back(f);
    }

    // Вывод ближайших дней рождения 
    if (!celebrate_today && !future_birthdays.empty()) {
        std::cout << "Ближайшие дни рождения:\n";
        for (const auto& f : future_birthdays) {
            std::tm b_this_year = f.birthday;
            b_this_year.tm_year = now->tm_year;
            std::time_t b_time = std::mktime(&b_this_year);
            int days_left = static_cast<int>(std::difftime(b_time, t) / 86400);

            if (days_left == min_days_left) {
                int display_month = f.birthday.tm_mon + 1;
                std::cout << " 📅 " << f.name << " — " 
                          << (f.birthday.tm_mday < 10 ? "0" : "") << f.birthday.tm_mday << "."
                          << (display_month < 10 ? "0" : "") << display_month << "\n";
            }
        }
    } else if (!celebrate_today && friends.empty()) {
        std::cout << "Список друзей пуст.\n";
    } else if (!celebrate_today && future_birthdays.empty()) {
        std::cout << "У всех друзей дни рождения в этом году уже прошли.\n";
    }

    std::cout << "----------------------------\n";
    return 0;
}
