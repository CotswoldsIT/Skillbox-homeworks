#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция для генерации бинарного файла 
void create_test_png() {
    std::ofstream out("fake.png", std::ios::binary);
    if (out.is_open()) {
        char png_signature[4] = {-119, 'P', 'N', 'G'};
        out.write(png_signature, 4);
        out.close();
    }
}

int main() {
    // Автоматически создаем правильный тестовый фай
    create_test_png();

    std::string file_path;
    std::cout << "=== Детектор PNG-файлов ===\n";
    std::cout << "Введите путь к файлу для проверки: ";
    std::getline(std::cin, file_path);

    // Проверяем расширение файла с конца строки с помощью substr 
    if (file_path.length() < 4 || file_path.substr(file_path.length() - 4) != ".png") {
        std::cout << "Результат: Это НЕ PNG-файл (неверное расширение файла).\n";
        return 0;
    }

    // Открываем файл для чтения первых байт
    std::ifstream file(file_path, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл по указанному пути!\n";
        return 1;
    }

    // Считываем первые 4 байта из файла
    char header[4];
    file.read(header, 4);
    file.close();

    // Проверяем, удалось ли прочитать ровно 4 байта
    if (file.gcount() < 4) {
        std::cout << "Результат: Это НЕ PNG-файл (файл слишком поврежден или мал).\n";
        return 0;
    }

    // Проверяем сигнатуру PNG 
    if (header[0] == -119 && header[1] == 'P' && header[2] == 'N' && header[3] == 'G') {
        std::cout << "Результат: Файл успешно прошёл проверку. Это настоящий PNG-файл!\n";
    } else {
        std::cout << "Результат: Это НЕ PNG-файл (заголовок не соответствует стандарту PNG).\n";
    }

    return 0;
}
