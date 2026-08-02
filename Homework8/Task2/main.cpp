#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string numberStr;
    std::cout << "Введите число: ";
    std::cin >> numberStr;

    // Пустая строка не может быть числом
    if (numberStr.empty()) {
        std::cout << "No\n";
        return 0;
    }

    int digitCount = 0;
    int dotCount = 0;
    bool isValid = true;

    // Проверка первого символ
    char first = numberStr[0];
    if (first == '-') {
        // Минус разрешен только первым символом
    } else if (first == '.') {
        dotCount++;
    } else if (first >= '0' && first <= '9') {
        digitCount++;
    } else {
        isValid = false;
    }

    // Проверка всех остальных символов
    if (isValid) {
        for (int i = 1; i < numberStr.length(); i++) {
            char ch = numberStr[i];
            if (ch >= '0' && ch <= '9') {
                digitCount++;
            } else if (ch == '.') {
                dotCount++;
            } else {
                // Любой другой символ (например, +, e, буквы) запрещен
                isValid = false;
                break;
            }
        }
    }

    // Финальная проверка: должна быть хотя бы одна цифра и не больше одной точки
    if (isValid && digitCount > 0 && dotCount <= 1) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
