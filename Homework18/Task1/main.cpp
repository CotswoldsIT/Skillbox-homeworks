#include <iostream>
#include <string>
#include <map>
#include <vector>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::map<std::string, std::string> phone_to_name;
    std::map<std::string, std::vector<std::string>> name_to_phones;

    std::cout << "=== Телефонный справочник ===\n";
    std::cout << "Примеры команд:\n";
    std::cout << "1. 69-70-30 Ivanov (добавить запись)\n";
    std::cout << "2. 69-70-30 (поиск фамилии по номеру)\n";
    std::cout << "3. Ivanov (поиск номеров по фамилии)\n";
    std::cout << "Введите 'exit' для завершения работы.\n\n";

    std::string input;
    while (true) {
        std::cout << "Запрос: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        // Очищаем случайные пробелы в самом конце строки
        while (!input.empty() && input.back() == ' ') {
            input.pop_back();
        }
        // Очищаем случайные пробелы в самом начале строки
        while (!input.empty() && input.front() == ' ') {
            input.erase(0, 1);
        }

        if (input.empty()) {
            continue;
        }

        size_t space_pos = input.find(' ');

        // Запрос типа 1: добавление (пробел разделяет два слова)
        if (space_pos != std::string::npos) {
            std::string phone = input.substr(0, space_pos);
            std::string name = input.substr(space_pos + 1);

            phone_to_name[phone] = name;
            name_to_phones[name].push_back(phone);

            std::cout << "Успешно добавлено: " << phone << " -> " << name << "\n";
        } 
        // Поиск по одному слову
        else {
            if (input[0] >= '0' && input[0] <= '9') {
                auto it = phone_to_name.find(input);
                if (it != phone_to_name.end()) {
                    std::cout << "Абонент: " << it->second << "\n";
                } else {
                    std::cout << "Ошибка: Номер не найден.\n";
                }
            } 
            else {
                auto it = name_to_phones.find(input);
                if (it != name_to_phones.end()) {
                    std::cout << "Номера телефона: ";
                    for (const auto& phone : it->second) {
                        std::cout << phone << " ";
                    }
                    std::cout << "\n";
                } else {
                    std::cout << "Ошибка: Абонент не найден.\n";
                }
            }
        }
    }

    return 0;
}
