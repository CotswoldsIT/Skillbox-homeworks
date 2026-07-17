#include <iostream>
#include <string>
#include <vector>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 50;

// Класс окна 
class Window {
public:
    int x = 10;
    int y = 10;
    int width = 20;
    int height = 15;
};

// Класс экрана монитора по рекомендации 
class Screen {
private:
    Window win;

public:
    // Метод смещения окна с проверкой границ 
    void move() {
        int dx, dy;
        std::cout << "Введите вектор смещения (dX dY): ";
        std::cin >> dx >> dy;

        int newX = win.x + dx;
        int newY = win.y + dy;

        // Корректируем координаты, чтобы окно не выходило за область экрана
        if (newX < 0) newX = 0;
        if (newY < 0) newY = 0;
        if (newX + win.width > SCREEN_WIDTH) newX = SCREEN_WIDTH - win.width;
        if (newY + win.height > SCREEN_HEIGHT) newY = SCREEN_HEIGHT - win.height;

        win.x = newX;
        win.y = newY;

        std::cout << "[Окно перемещено] Новые координаты левого верхнего угла: (" << win.x << ", " << win.y << ")\n";
    }

    // Метод изменения размеров с проверкой 
    void resize() {
        int newWidth, newHeight;
        std::cout << "Введите новый размер окна (Ширина Высота): ";
        std::cin >> newWidth >> newHeight;

        if (newWidth < 0 || newHeight < 0) {
            std::cout << "Ошибка: Размеры окна не могут быть отрицательными!\n";
            return;
        }

        // Если новое окно при текущей позиции вылазит за границы экрана, сжимаем его до краев монитора
        if (win.x + newWidth > SCREEN_WIDTH) {
            newWidth = SCREEN_WIDTH - win.x;
        }
        if (win.y + newHeight > SCREEN_HEIGHT) {
            newHeight = SCREEN_HEIGHT - win.y;
        }

        win.width = newWidth;
        win.height = newHeight;

        std::cout << "[Размер изменен] Новые размеры: " << win.width << " x " << win.height << "\n";
    }

    // Метод отрисовки матрицы экрана  (0 — фон, 1 — окно)
    void display() const {
        std::cout << "\n--- ИЗОБРАЖЕНИЕ МОНИТОРА ---\n";
        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                // Проверяем, попадает ли текущий пиксель внутрь окна
                if (x >= win.x && x < win.x + win.width && y >= win.y && y < win.y + win.height) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }
            std::cout << "\n";
        }
        std::cout << "----------------------------\n";
    }
};

int main() {
    Screen myScreen;

    std::cout << "=== Управление окном рабочего стола ===\n";
    std::cout << "Размер виртуального экрана: " << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << "\n";
    std::cout << "Доступные команды: move, resize, display, close\n\n";

    std::string command;
    while (true) {
        std::cout << "\nВведите команду: ";
        std::cin >> command;

        if (command == "close") {
            std::cout << "Работа программы завершена. Окно закрыто.\n";
            break;
        }
        else if (command == "move") {
            myScreen.move();
        }
        else if (command == "resize") {
            myScreen.resize();
        }
        else if (command == "display") {
            myScreen.display();
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова.\n";
        }
    }

    return 0;
}
