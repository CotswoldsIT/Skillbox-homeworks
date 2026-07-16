#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Структура данных для ведомости 
struct PaymentRecord {
    std::string firstName;
    std::string lastName;
    std::string date;
    int amount = 0;
};

int main() {
    std::string command;
    std::cout << "=== Ведомость учёта на структурах ===\n";
    std::cout << "Введите команду (list — показать ведомость, add — добавить запись, ввод производится латинскими буквами): ";
    std::cin >> command;

    if (command == "list") {
        // Проверяем существование файла на диске  
        std::ifstream file("statement.txt");
        if (!file.is_open()) {
            std::cout << "Предупреждение: Файл ведомости statement.txt не найден на диске.\n";
            return 0;
        }

        std::vector<PaymentRecord> records;
        
        while (true) {
            PaymentRecord tempRecord;
            //  отдельно считываем первое поле для проверки EOF
            file >> tempRecord.firstName;
            if (file.eof()) {
                break;
            }
            
            // Дочитываем остальные поля структуры
            file >> tempRecord.lastName >> tempRecord.date >> tempRecord.amount;
            records.push_back(tempRecord);
        }
        file.close();

        if (records.empty()) {
            std::cout << "Ведомость пуста.\n";
        } else {
            std::cout << "\n--- СОДЕРЖИМОЕ ВЕДОМОСТИ ---\n";
            for (const auto& record : records) {
                std::cout << record.firstName << " " << record.lastName << " "
                          << record.date << " " << record.amount << " руб.\n";
            }
            std::cout << "----------------------------\n";
        }

    } else if (command == "add") {
        PaymentRecord newRecord;
        std::cout << "Введите имя: ";
        std::cin >> newRecord.firstName;
        std::cout << "Введите фамилию: ";
        std::cin >> newRecord.lastName;
        std::cout << "Введите дату (ДД.ММ.ГГГГ): ";
        std::cin >> newRecord.date;
        std::cout << "Введите сумму выплаты (руб.): ";
        std::cin >> newRecord.amount;

        // Открываем на запись в конец файла (ios::app)
        std::ofstream file("statement.txt", std::ios::app);
        if (!file.is_open()) {
            std::cout << "Ошибка: Не удалось открыть файл для записи!\n";
            return 1;
        }

        // Записываем структуру в файл в нужном формате
        file << newRecord.firstName << " " << newRecord.lastName << " "
             << newRecord.date << " " << newRecord.amount << "\n";
        file.close();

        std::cout << "Запись успешно добавлена на структурах!\n";

    } else {
        std::cout << "Ошибка: Неизвестная команда.\n";
    }

    return 0;
}
