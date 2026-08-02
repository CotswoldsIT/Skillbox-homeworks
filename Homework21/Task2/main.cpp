#include <iostream>
#include <string>
#include <vector>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Класс записи в адресной книге 
class Contact {
public:
    std::string name;
    std::string phoneNumber;
};

// Класс мобильного телефона 
class Phone {
private:
    std::vector<Contact> addressBook;

    // Вспомогательный приватный метод поиска номера по имени или по самому номеру
    std::string findNumber(const std::string& query) const {
        for (const auto& contact : addressBook) {
            if (contact.name == query || contact.phoneNumber == query) {
                return contact.phoneNumber;
            }
        }
        // Если это строка формата +7 и состоит из цифр, возвращаем её как есть
        if (query.rfind("+7", 0) == 0 && query.length() == 12) {
            return query;
        }
        return "";
    }

public:
    // Метод добавления контакта 
    void add() {
        Contact newContact;
        std::cout << "Введите имя контакта: ";
        std::cin >> newContact.name;
        std::cout << "Введите номер телефона (+7XXXXXXXXXX): ";
        std::cin >> newContact.phoneNumber;

        // Базовая валидация формата номера 
        if (newContact.phoneNumber.length() != 12 || newContact.phoneNumber.rfind("+7", 0) != 0) {
            std::cout << "Ошибка: Неверный формат номера! Номер должен начинаться с +7 и содержать 10 цифр.\n";
            return;
        }

        addressBook.push_back(newContact);
        std::cout << "Контакт \"" << newContact.name << "\" успешно добавлен!\n";
    }

    // Метод вызова абонента 
    void call() const {
        std::string query;
        std::cout << "Введите имя контакта или номер телефона: ";
        std::cin >> query;

        std::string targetNumber = findNumber(query);

        if (!targetNumber.empty()) {
            std::cout << "📞 CALL " << targetNumber << "\n";
        } else {
            std::cout << "Ошибка: Не удалось выполнить вызов. Контакт не найден или неверный номер.\n";
        }
    }

    // Метод отправки СМС 
    void sms() const {
        std::string query;
        std::cout << "Введите имя контакта или номер телефона: ";
        std::cin >> query;

        std::string targetNumber = findNumber(query);

        if (!targetNumber.empty()) {
            std::string message;
            std::cout << "Введите текст сообщения: ";
            std::cin.ignore(); // Очищаем буфер потока ввода
            std::getline(std::cin, message);

            std::cout << "✉️ СМС отправлено на номер " << targetNumber << " с текстом: \"" << message << "\"\n";
        } else {
            std::cout << "Ошибка: Не удалось отправить СМС. Контакт не найден.\n";
        }
    }
};

int main() {
    Phone myPhone;

    std::cout << "=== Симуляция мобильного телефона ===\n";
    std::cout << "Доступные команды: add, call, sms, exit\n\n";

    std::string command;
    while (true) {
        std::cout << "\nВведите команду: ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Работа симулятора телефона завершена.\n";
            break;
        }
        else if (command == "add") {
            myPhone.add();
        }
        else if (command == "call") {
            myPhone.call();
        }
        else if (command == "sms") {
            myPhone.sms();
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова.\n";
        }
    }

    return 0;
}
