#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int number = 0;
    std::cout << "Ввод: ";
    std::cin >> number;

    // Контроль ввода по правилам задачи
    if (number < 1 || number > 3999) {
        std::cout << "Ошибка! Число должно быть в диапазоне от 1 до 3999.\n";
        return 1;
    }

    // Массив арабских чисел, включая исключения для 4 и 9
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    
    // Соответствующий массив римских символов
    std::string romanSymbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    std::string result = "";

    // Проходим по всем номиналам сверху вниз
    for (int i = 0; i < 13; i++) {
        // Пока число больше или равно текущему номиналу, вычитаем его и добавляем букву
        while (number >= values[i]) {
            result += romanSymbols[i];
            number -= values[i];
        }
    }

    std::cout << "Вывод: " << result << "\n";

    return 0;
}
