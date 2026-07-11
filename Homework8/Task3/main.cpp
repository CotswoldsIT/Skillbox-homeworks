#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string text;
    std::cout << "Введите строку: ";
    // Читаем всю строку с пробелами
    std::getline(std::cin, text);

    int wordCount = 0;
    bool inWord = false; // Флаг, который показывает, находимся ли мы сейчас внутри слова

    // Перебираем каждый символ в строке
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];

        if (ch != ' ') {
            // Если символ — не пробел и мы ещё не внутри слова, значит началось новое слово
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        } else {
            // Если встретили пробел, значит слово закончилось
            inWord = false;
        }
    }

    std::cout << "\nОтвет: " << wordCount << "\n";

    return 0;
}
