#include <iostream>
#include <vector>
#include <string>
#include <limits> 
#include <windows.h> 

// Настройка русского языка для Windows консоли (UTF-8)
auto locale_init_in = SetConsoleCP(65001);
auto locale_init_out = SetConsoleOutputCP(65001);

// Шаблонная структура для хранения пары ключ-значение
template <typename K, typename V>
struct RegistryPair {
    K key;
    V value;
};

// Шаблонный класс реестра данных
template <typename K, typename V>
class Registry {
private:
    std::vector<RegistryPair<K, V>> items;

public:
    // добавить элемент с ключом
    void add(const K& key, const V& value) {
        items.push_back({key, value});
        std::cout << "Элемент успешно добавлен в реестр.\n";
    }

    // удалить все элементы с заданным ключом
    void remove(const K& key) {
        size_t initialSize = items.size();
        
        // Идем с конца вектора, чтобы безопасно удалять элементы по индексу
        for (int i = static_cast<int>(items.size()) - 1; i >= 0; --i) {
            if (items[i].key == key) {
                items.erase(items.begin() + i);
            }
        }
        
        size_t removedCount = initialSize - items.size();
        if (removedCount > 0) {
            std::cout << "Успешно удалено элементов с таким ключом: " << removedCount << "\n";
        } else {
            std::cout << "Элементы с таким ключом не найдены в реестре.\n";
        }
    }

    // напечатать на экране все элементы с их ключами
    void print() const {
        if (items.empty()) {
            std::cout << "[Реестр пуст]\n";
            return;
        }
        std::cout << "--- ТЕКУЩЕЕ СОДЕРЖИМОЕ РЕЕСТРА ---\n";
        for (const auto& item : items) {
            std::cout << "  Ключ: " << item.key << " -> Значение: " << item.value << "\n";
        }
        std::cout << "----------------------------------\n";
    }

    // найти все элементы по их ключу
    void find(const K& key) const {
        bool found = false;
        std::cout << "--- РЕЗУЛЬТАТЫ ПОИСКА ДЛЯ КЛЮЧА '" << key << "' ---\n";
        for (const auto& item : items) {
            if (item.key == key) {
                std::cout << "  Найдено значение: " << item.value << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "  Совпадений не найдено.\n";
        }
        std::cout << "----------------------------------------\n";
    }
};

int main() {
    // Создаем реестр
    Registry<std::string, int> reg;

    std::cout << "=== ШАБЛОННЫЙ РЕЕСТР ДАННЫХ ===\n";
    std::cout << "Доступные команды:\n";
    std::cout << "  add [ключ] [значение]  - Добавить элемент\n";
    std::cout << "  remove [ключ]          - Удалить ВСЕ элементы с этим ключом\n";
    std::cout << "  find [ключ]            - Найти все элементы по ключу\n";
    std::cout << "  print                  - Вывести весь реестр\n";
    std::cout << "  exit                   - Выход из программы\n\n";

    std::string command;

    while (true) {
        std::cout << "Введите команду: ";
        if (!(std::cin >> command)) break;

        if (command == "exit") {
            break;
        }
        else if (command == "add") {
            std::string key;
            int value;
            if (std::cin >> key >> value) {
                reg.add(key, value);
            } else {
                std::cout << "Ошибка параметров! Формат: add [строка-ключ] [число-значение]\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (command == "remove") {
            std::string key;
            if (std::cin >> key) {
                reg.remove(key);
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (command == "find") {
            std::string key;
            if (std::cin >> key) {
                reg.find(key);
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else if (command == "print") {
            reg.print();
        }
        else {
            std::cout << "Неизвестная команда! Доступны: add, remove, find, print, exit.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "\n";
    }

    std::cout << "Программа завершена.\n";
    return 0;
}
