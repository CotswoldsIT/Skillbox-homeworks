#include <iostream>
#include <string>

// Функция выделения конкретной части (октета) IP-адреса по его индексу (0, 1, 2, 3)
std::string get_address_part(std::string ip, int part_index) {
    std::string result = "";
    int current_part = 0;

    for (size_t i = 0; i < ip.length(); ++i) {
        if (ip[i] == '.') {
            current_part++;
            continue;
        }
        if (current_part == part_index) {
            result += ip[i];
        }
    }
    return result;
}

// Функция проверки отдельного октета на корректность
bool validate_part(std::string part) {
    // Число не может быть пустым или длиннее 3 знаков
    if (part.empty() || part.length() > 3) return false;

    // Проверяем, что все символы являются цифрами
    for (size_t i = 0; i < part.length(); ++i) {
        if (part[i] < '0' || part[i] > '9') return false;
    }

    // Проверка на ведущие нули (например, "01" или "000")
    if (part.length() > 1 && part[0] == '0') return false;

    // Переводим строку в число int для проверки диапазона
    int value = std::stoi(part);
    if (value < 0 || value > 255) return false;

    return true;
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string ip;
    std::cout << "Введите IP-адрес для проверки: ";
    std::cin >> ip;

    // Считаем количество точек в строке
    int dot_count = 0;
    for (size_t i = 0; i < ip.length(); ++i) {
        if (ip[i] == '.') dot_count++;
    }

    // Если точек не ровно 3, адрес автоматически некорректен
    if (dot_count != 3) {
        std::cout << "Invalid" << std::endl;
        return 0;
    }

    // Извлекаем и проверяем все 4 части
    bool is_valid = true;
    for (int i = 0; i < 4; ++i) {
        std::string part = get_address_part(ip, i);
        if (!validate_part(part)) {
            is_valid = false;
            break;
        }
    }

    // Выводим итоговый вердикт
    if (is_valid) {
        std::cout << "Valid" << std::endl;
    } else {
        std::cout << "Invalid" << std::endl;
    }

    return 0;
}
