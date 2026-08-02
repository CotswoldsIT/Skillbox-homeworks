#include <iostream>
#include <fstream> // Библиотека для работы с файловыми потоками
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    // Открываем файл по указанному пути для чтения
    std::ifstream file("words.txt");

    // Контроль открытия файла
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл words.txt!\n";
        std::cout << "Убедитесь, что файл создан и лежит в одной папке с main.cpp.\n";
        return 1;
    }

    std::string search_word;
    std::cout << "=== Программа поиска слов в файле ===\n";
    std::cout << "Введите слово для поиска: ";
    std::cin >> search_word;

    std::string current_word;
    int count = 0;

    // Считываем разные типы данных (в данном случае строки) из текстового файла пословно
    while (file >> current_word) {
        if (current_word == search_word) {
            count++;
        }
    }

    // Закрываем файл после работы
    file.close();

    std::cout << "Слово \"" << search_word << "\" найдено в файле. Количество повторений: " << count << "\n";

    return 0;
}
