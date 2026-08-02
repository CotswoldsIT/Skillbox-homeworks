#include <iostream>
#include <string>
#include "surgery.h" // Подключаем наш заголовочный файл

auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::cout << "=== Симулятор медицинской операции ===\n";
    std::cout << "Доступные инструменты: scalpel, hemostat, tweezers, suture\n";
    std::cout << "ВНИМАНИЕ: Любая операция должна начинаться со scalpel!\n\n";

    Point cut_start, cut_end;
    bool operation_started = false;

    while (true) {
        std::string command;
        std::cout << "\nВведите инструмент: ";
        std::cin >> command;

        if (!operation_started) {
            if (command == "scalpel") {
                std::cout << "Точка начала разреза";
                cut_start = input_point();
                std::cout << "Точка конца разреза";
                cut_end = input_point();
                
                use_scalpel(cut_start, cut_end);
                operation_started = true;
            } else {
                std::cout << "Ошибка! Нельзя использовать другие инструменты до разреза скальпелем.\n";
            }
            continue;
        }

        // Если операция уже идет
        if (command == "hemostat") {
            Point p = input_point();
            use_hemostat(p);
        } 
        else if (command == "tweezers") {
            Point p = input_point();
            use_tweezers(p);
        } 
        else if (command == "scalpel") {
            std::cout << "Точка начала дополнительного разреза";
            Point start = input_point();
            std::cout << "Точка конца дополнительного разреза";
            Point end = input_point();
            use_scalpel(start, end);
        } 
        else if (command == "suture") {
            std::cout << "Точка начала шва";
            Point suture_start = input_point();
            std::cout << "Точка конца шва";
            Point suture_end = input_point();

            use_suture(suture_start, suture_end);

            // Проверяем совпадение координат начала и конца шва с начальным разрезом 
            if (are_equal(cut_start, suture_start) && are_equal(cut_end, suture_end)) {
                std::cout << "\n🎉 Операция успешно завершена! Пациент спасен.\n";
                break;
            } else {
                std::cout << "Разрез зашит не полностью или не в том месте! Продолжайте операцию.\n";
            }
        } 
        else {
            std::cout << "Неизвестный инструмент. Попробуйте снова.\n";
        }
    }

    return 0;
}
