#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::string file_path;
    std::cout << "=== Просмотрщик текстовых файлов ===\n";
    std::cout << "Введите путь к файлу для просмотра: ";
    std::getline(std::cin, file_path);

    // Открываем файл
    std::ifstream file(file_path, std::ios::binary);

    // Проверяем, был ли на самом деле открыт файл
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл по указанному пути!\n";
        return 1;
    }

    // Создаем буфер для постепенного чтения файла фрагментами
    const int buffer_size = 256;
    char buffer[buffer_size];

    std::cout << "\n--- Содержимое файла ---\n";

    // Считываем файл постепенно отдельными фрагментами
    while (file.read(buffer, buffer_size - 1)) {
        // Добавляем ноль, чтобы корректно вывести фрагмент как строку
        buffer[file.gcount()] = '\0';
        std::cout << buffer;
    }

    // Дочитываем последний оставшийся фрагмент файла
    if (file.gcount() > 0) {
        buffer[file.gcount()] = '\0';
        std::cout << buffer;
    }

    std::cout << "\n------------------------\n";
    file.close();

    return 0;
}
