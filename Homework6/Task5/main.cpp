#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Размеры сетки
    int height = 20;
    int width = 50;

    // Координаты центра
    int centerY = 10;
    int centerX = 25;

    std::cout << "=== Рисование координатных осей ===\n\n";

    // Цикл по строкам
    for (int row = 1; row <= height; row++) {
        // Цикл по столбцам
        for (int col = 1; col <= width; col++) {
            
            // Центр осей
            if (row == centerY && col == centerX) {
                std::cout << "+";
            }
            // Стрелка вверх
            else if (row == 1 && col == centerX) {
                std::cout << "^";
            }
            // Стрелка вправо
            else if (row == centerY && col == width) {
                std::cout << ">";
            }
            // Вертикальная ось
            else if (col == centerX) {
                std::cout << "|";
            }
            // Горизонтальная ось
            else if (row == centerY) {
                std::cout << "-";
            }
            // Пустые места
            else {
                std::cout << " ";
            }
        }
        // Перенос строки
        std::cout << "\n";
    }

    return 0;
}
