#include <iostream>
#include <string>
#include <cmath>
#include <clocale>   
#include <windows.h> // Нужен для точной настройки кодировки 

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Структура для размеров описывающего прямоугольника
struct BoundingBoxDimensions {
    double width;
    double height;
};

// Интерфейс Геометрическая фигура
class Shape {
public:
    virtual ~Shape() = default; // Виртуальный деструктор
    virtual double square() = 0; // виртуальный метод площади
    virtual BoundingBoxDimensions dimensions() = 0; // Размеры описывающего прямоугольника
    virtual std::string type() = 0; // Название типа фигуры
};

// Класс Круг
class Circle : public Shape {
private:
    double radius;
    const double PI = 3.14159265358979323846;

public:
    Circle(double in_radius) : radius(in_radius) {}

    double square() override {
        return PI * radius * radius;
    }

    BoundingBoxDimensions dimensions() override {
        return { radius * 2.0, radius * 2.0 };
    }

    std::string type() override {
        return "Circle";
    }
};

// Класс Прямоугольник 
class Rect : public Shape {
private:
    double width;
    double height;

public:
    Rect(double in_width, double in_height) : width(in_width), height(in_height) {}

    double square() override {
        return width * height;
    }

    BoundingBoxDimensions dimensions() override {
        return { width, height };
    }

    std::string type() override {
        return "Rectangle";
    }
};

// Класс Треугольник
class Triangle : public Shape {
private:
    double a, b, c;

public:
    Triangle(double in_a, double in_b, double in_c) : a(in_a), b(in_b), c(in_c) {}

    double square() override {
        double p = (a + b + c) / 2.0; 
        return std::sqrt(p * (p - a) * (p - b) * (p - c)); 
    }

    BoundingBoxDimensions dimensions() override {
        double s = square(); // Вызываем уже готовый метод площади
        
        // Находим радиус описанной окружности: (a * b * c) / (4 * S)
        double r = (a * b * c) / (4.0 * s);
        
        // Сторона описывающего квадрата равна 2 * r
        double side = r * 2.0;
        return { side, side };
    }

    std::string type() override {
        return "Triangle";
    }
};

// Общая функция вывода параметров 
void printParams(Shape *shape) {
    if (shape == nullptr) return;
    
    BoundingBoxDimensions box = shape->dimensions();
    
    std::cout << "Type: " << shape->type() << std::endl;
    std::cout << "Square: " << shape->square() << std::endl;
    std::cout << "Width: " << box.width << std::endl;
    std::cout << "Height: " << box.height << std::endl;
}

int main() {
    SetConsoleCP(65001);       
    SetConsoleOutputCP(65001); 

    std::cout << "=== Тестирование интерфейса Shape ===\n\n";

    Triangle t(3, 4, 5); 
    printParams(&t);
    std::cout << "\n------------------------------------\n";

    Rect rect(4, 6);
    printParams(&rect);
    std::cout << "\n------------------------------------\n";

    Circle circle(5);
    printParams(&circle);
    std::cout << "\n------------------------------------\n";

    return 0;
}
