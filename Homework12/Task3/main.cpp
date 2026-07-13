#include <iostream>
#include <string>
#include <sstream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::string buffer;
    
    std::cout << "=== Строковый калькулятор ===\n";
    std::cout << "Введите выражение в формате <число1><действие><число2> (например, 10.5+4.5 или 15,5*2):\n";
    std::cin >> buffer;

    // Автозамена: превращаем все запятые в точки для стабильности std::stringstream
    for (int i = 0; i < buffer.length(); ++i) {
        if (buffer[i] == ',') {
            buffer[i] = '.';
        }
    }

    // Оборачиваем строку в поток по рекомендации из ТЗ
    std::stringstream buffer_stream(buffer);
    
    double a;
    char operation;
    double b;

    // Распарсиваем строку на отдельные члены
    if (buffer_stream >> a >> operation >> b) {
        double result = 0.0;
        bool valid_op = true;

        // Выполняем математическое действие
        if (operation == '+') {
            result = a + b;
        } else if (operation == '-') {
            result = a - b;
        } else if (operation == '*') {
            result = a * b;
        } else if (operation == '/') {
            // Контроль деления на ноль
            if (b == 0.0) {
                std::cout << "Ошибка: Деление на ноль невозможно!\n";
                return 0;
            }
            result = a / b;
        } else {
            std::cout << "Ошибка: Неизвестная операция '" << operation << "'!\n";
            valid_op = false;
        }

        if (valid_op) {
            std::cout << "Результат: " << result << "\n";
        }
    } else {
        std::cout << "Ошибка: Неверный формат ввода выражения!\n";
    }

    return 0;
}
