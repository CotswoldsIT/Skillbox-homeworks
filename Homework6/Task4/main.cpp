#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Переменные для размеров рамки
    int width, height;
    
    std::cout << "Введите ширину и высоту рамки: ";
    std::cin >> width >> height;

    // Проверка, чтобы размеры не были слишком маленькими
    if (width < 2 || height < 2) {
        std::cout << "Ошибка! Размеры рамки должны быть не меньше 2.\n";
        return 1;
    }

    // Цикл по строкам (высота)
    for (int row = 1; row <= height; row++) {
        // Цикл по символам в строке (ширина)
        for (int col = 1; col <= width; col++) {
            
            // Забор по краям
            if (col == 1 || col == width) {
                std::cout << "|";
            } 
            // Верхняя и нижняя границы
            else if (row == 1 || row == height) {
                std::cout << "-";
            } 
            // Пустое место внутри
            else {
                std::cout << " ";
            }
        }
        // Переход на новую строку
        std::cout << "\n";
    }

    return 0;
}
