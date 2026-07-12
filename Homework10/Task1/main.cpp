#include <iostream>
#include <string>

// Функция для шифрования текста методом Цезаря
std::string encrypt_caesar(std::string text, int key) {
    // Сокращаем сдвиг, так как в алфавите всего 26 букв
    key = key % 26;
    
    // Если сдвиг отрицательный, переводим его в положительный эквивалент
    if (key < 0) {
        key += 26;
    }

    // Проходим по каждому символу строки
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];

        // Если это большая английская буква
        if (c >= 'A' && c <= 'Z') {
            text[i] = 'A' + (c - 'A' + key) % 26;
        }
        // Если это маленькая английская буква
        else if (c >= 'a' && c <= 'z') {
            text[i] = 'a' + (c - 'a' + key) % 26;
        }
        // Все остальные символы (знаки препинания, пробелы, цифры) не трогаем
    }

    return text;
}

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string text;
    int key = 0;

    std::cout << "=== Шифр Цезаря ===\n";
    std::cout << "Введите текст для шифрования: ";
    std::getline(std::cin, text); // Используем getline, чтобы считывать строки с пробелами

    std::cout << "Введите сдвиг (число): ";
    std::cin >> key;

    // Вызываем функцию шифрования
    std::string encryptedText = encrypt_caesar(text, key);

    std::cout << "\nРезультат:\n" << encryptedText << std::endl;

    return 0;
}
