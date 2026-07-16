#include <iostream>
#include <string>
#include <cmath> // Для std::sqrt

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Структура двумерного математического вектора
struct Vector2D {
    double x = 0.0;
    double y = 0.0;
};

// Сложение двух векторов
Vector2D add(const Vector2D& v1, const Vector2D& v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

// Вычитание двух векторов
Vector2D subtract(const Vector2D& v1, const Vector2D& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

// Умножение вектора на скаляр
Vector2D scale(const Vector2D& v, double scalar) {
    return {v.x * scalar, v.y * scalar};
}

// Нахождение длины вектора
double length(const Vector2D& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Нормализация вектора
Vector2D normalize(const Vector2D& v) {
    double len = length(v);
    if (len == 0.0) {
        std::cout << "Предупреждение: Нельзя нормализовать нулевой вектор.\n";
        return {0.0, 0.0};
    }
    return {v.x / len, v.y / len};
}

//  функция вывода вектора на экран
void print_vector(const Vector2D& v) {
    std::cout << "Результат (вектор): (" << v.x << ", " << v.y << ")\n";
}

int main() {
    std::string command;
    std::cout << "=== Калькулятор двумерных векторов ===\n";
    std::cout << "Доступные команды: add, subtract, scale, length, normalize\n";
    std::cout << "Введите команду: ";
    std::cin >> command;

    if (command == "add") {
        Vector2D v1, v2;
        std::cout << "Введите координаты первого вектора (X Y): ";
        std::cin >> v1.x >> v1.y;
        std::cout << "Введите координаты второго вектора (X Y): ";
        std::cin >> v2.x >> v2.y;
        
        print_vector(add(v1, v2));

    } else if (command == "subtract") {
        Vector2D v1, v2;
        std::cout << "Введите координаты первого вектора (X Y): ";
        std::cin >> v1.x >> v1.y;
        std::cout << "Введите координаты второго вектора (X Y): ";
        std::cin >> v2.x >> v2.y;
        
        print_vector(subtract(v1, v2));

    } else if (command == "scale") {
        Vector2D v;
        double scalar;
        std::cout << "Введите координаты вектора (X Y): ";
        std::cin >> v.x >> v.y;
        std::cout << "Введите скалярное значение (число): ";
        std::cin >> scalar;
        
        print_vector(scale(v, scalar));

    } else if (command == "length") {
        Vector2D v;
        std::cout << "Введите координаты вектора (X Y): ";
        std::cin >> v.x >> v.y;
        
        std::cout << "Результат (длина): " << length(v) << "\n";

    } else if (command == "normalize") {
        Vector2D v;
        std::cout << "Введите координаты вектора (X Y): ";
        std::cin >> v.x >> v.y;
        
        print_vector(normalize(v));

    } else {
        std::cout << "Ошибка: Неизвестная команда.\n";
    }

    return 0;
}
