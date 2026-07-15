#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::cout << "=== Симулятор игры «Рыбалка» ===\n";

    // Открываем исходный файл реки для чтения 
    std::ifstream river_file("river.txt");
    if (!river_file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл river.txt!\n";
        std::cout << "Убедитесь, что создали файл river.txt со списком рыб в папке с main.cpp.\n";
        return 1;
    }

    std::string target_fish;
    std::cout << "Какую рыбу вы хотите поймать? (например: carp, bass, shad): ";
    std::cin >> target_fish;

    // Открываем файл корзины в режиме добавления (ios::app) 
    std::ofstream basket_file("basket.txt", std::ios::app);
    if (!basket_file.is_open()) {
        std::cout << "Ошибка: Не удалось открыть или создать файл basket.txt!\n";
        river_file.close();
        return 1;
    }

    std::string current_fish;
    int catch_count = 0;

    // Построчно читаем реку и ищем нужный вид рыбы
    while (river_file >> current_fish) {
        if (current_fish == target_fish) {
            basket_file << current_fish << "\n"; // Добавляем улов в корзину
            catch_count++;
        }
    }

    // Закрываем оба файловых потока 
    river_file.close();
    basket_file.close();

    std::cout << "\nЛовля завершена!\n";
    std::cout << "За эту сессию поймано рыб вида \"" << target_fish << "\": " << catch_count << "\n";
    std::cout << "Все пойманные рыбы сохранены в файле basket.txt.\n";

    return 0;
}
