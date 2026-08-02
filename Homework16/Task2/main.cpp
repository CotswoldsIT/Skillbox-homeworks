#include <iostream>
#include <fstream>
#include <cstdlib> // Библиотека для rand() и srand()
#include <ctime>   // Библиотека для time()

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    // Устанавливаем начальное зерно случайных чисел от текущего времени 
    std::srand(std::time(nullptr));

    int width = 0;
    int height = 0;

    std::cout << "=== Генератор случайных картин ===\n";
    std::cout << "Введите ширину картины (в пикселях): ";
    std::cin >> width;
    std::cout << "Введите высоту картины (в пикселях): ";
    std::cin >> height;

    if (width <= 0 || height <= 0) {
        std::cout << "Ошибка: Размеры картины должны быть больше нуля!\n";
        return 1;
    }

    // Открываем текстовый файл на запись
    std::ofstream file("pic.txt");

    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось создать файл pic.txt!\n";
        return 1;
    }

    // Генерируем двумерную картину построчно
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Генерируем случайный 0 или 1
            int pixel = std::rand() % 2;
            file << pixel << " ";
        }
        file << "\n"; // Перевод строки в конце каждого ряда пикселей
    }

    file.close();
    std::cout << "Картина успешно сохранена в файл pic.txt!\n";

    return 0;
}
