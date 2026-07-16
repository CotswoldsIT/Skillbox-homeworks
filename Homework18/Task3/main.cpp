#include <iostream>
#include <string>
#include <map>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция проверки анаграммы на std::map 
bool is_anagram(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    std::map<char, int> char_count;

    // Считаем буквы в первой строке
    for (char c : str1) {
        char_count[c]++;
    }

    // Вычитаем буквы второй строки
    for (char c : str2) {
        char_count[c]--;
    }

    // Если все счётчики обнулились, значит буквы совпали идеально
    for (const auto& pair : char_count) {
        if (pair.second != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    std::string word1, word2;
    std::cout << "=== Проверка на анаграмму ===\n";
    std::cout << "Пример ввода на латинице: lekarstvo steklovar\n";
    
    std::cout << "Введите первое слово: ";
    std::cin >> word1;
    std::cout << "Введите второе слово: ";
    std::cin >> word2;

    if (is_anagram(word1, word2)) {
        std::cout << "Результат: true (Строки являются анаграммами)\n";
    } else {
        std::cout << "Результат: false (Строки НЕ являются анаграммами)\n";
    }

    return 0;
} 