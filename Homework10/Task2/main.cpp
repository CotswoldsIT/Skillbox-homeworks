#include <iostream>
#include <string>

// Функция получения первой (локальной) части адреса до знака @
std::string get_local_part(std::string email) {
    std::string result = "";
    for (size_t i = 0; i < email.length(); ++i) {
        if (email[i] == '@') break;
        result += email[i]; // Накапливаем символы до @
    }
    return result;
}

// Функция получения второй (доменной) части адреса после знака @
std::string get_domain_part(std::string email) {
    std::string result = "";
    bool found_at = false;
    for (size_t i = 0; i < email.length(); ++i) {
        if (found_at) {
            result += email[i]; // Накапливаем символы после @
        }
        if (email[i] == '@') {
            found_at = true;
        }
    }
    return result;
}

// Функция валидации символов с помощью строк-словарей
bool validate_chars(std::string part, std::string dictionary) {
    for (size_t i = 0; i < part.length(); ++i) {
        bool found = false;
        // Каждый символ адреса сравниваем с каждым символом из словаря
        for (size_t j = 0; j < dictionary.length(); ++j) {
            if (part[i] == dictionary[j]) {
                found = true;
                break;
            }
        }
        if (!found) return false; // Если символа нет в словаре, часть невалидна
    }
    return true;
}

// Проверка общих правил для точек
bool check_dots(std::string part) {
    if (part.empty()) return false;
    if (part.front() == '.' || part.back() == '.') return false;
    
    for (size_t i = 0; i < part.length(); ++i) {
        if (part[i] == '.' && i + 1 < part.length() && part[i + 1] == '.') {
            return false; // Две точки подряд запрещены
        }
    }
    return true;
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string email;
    std::cout << "Введите email-адрес: ";
    std::cin >> email;

    // Считаем количество знаков '@' в строке
    int at_count = 0;
    for (size_t i = 0; i < email.length(); ++i) {
        if (email[i] == '@') at_count++;
    }

    // Если знак '@' отсутствует или их несколько — адрес некорректен
    if (at_count != 1) {
        std::cout << "No" << std::endl;
        return 0;
    }

    // Разделяем email на две части с помощью наших функций
    std::string local = get_local_part(email);
    std::string domain = get_domain_part(email);

    // Проверяем ограничения по длине частей
    if (local.length() < 1 || local.length() > 64 || domain.length() < 1 || domain.length() > 63) {
        std::cout << "No" << std::endl;
        return 0;
    }

    // Объявляем строки-словари допустимых символов
    std::string base_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.";
    std::string local_dictionary = base_chars + "!#$%&'*+/=?^_`{|}~";
    std::string domain_dictionary = base_chars; // Во второй части спецсимволы запрещены

    // Итоговая проверка всех условий
    if (check_dots(local) && check_dots(domain) && 
        validate_chars(local, local_dictionary) && 
        validate_chars(domain, domain_dictionary)) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}
