#include <iostream>
#include <string>
#include <cmath>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Перечисление цветов 
enum Color {
    NONE,
    RED,
    BLUE,
    GREEN
};

// Структура для представления описывающего прямоугольника
struct BoundingBox {
    double width = 0.0;
    double height = 0.0;
};

// Базовый класс иерархии 
class Shape {
protected:
    double centerX = 0.0;
    double centerY = 0.0;
    Color color = NONE;

public:
    // Конструктор базового класса с использованием указателя this 
    Shape(double centerX, double centerY, Color color) {
        this->centerX = centerX;
        this->centerY = centerY;
        this->color = color;
    }

    // Виртуальные методы, переопределяемые в дочерних классах
    virtual double area() const = 0;
    virtual BoundingBox boundingBox() const = 0;
    virtual ~Shape() {} // Виртуальный деструктор для безопасного ООП
};

// Класс Круг
class Circle : public Shape {
private:
    double radius = 0.0;

public:
    Circle(double centerX, double centerY, Color color, double radius) 
        : Shape(centerX, centerY, color) {
        this->radius = radius;
    }

    double area() const override {
        // Формула площади круга по ТЗ: atan(1) * 4 * radius * radius
        return std::atan(1.0) * 4.0 * this->radius * this->radius;
    }

    BoundingBox boundingBox() const override {
        // Описывающий прямоугольник круга — это квадрат со стороной 2*R
        return {this->radius * 2.0, this->radius * 2.0};
    }
};

// Класс Прямоугольник
class Rectangle : public Shape {
protected:
    double width = 0.0;
    double height = 0.0;

public:
    Rectangle(double centerX, double centerY, Color color, double width, double height) 
        : Shape(centerX, centerY, color) {
        this->width = width;
        this->height = height;
    }

    double area() const override {
        return this->width * this->height;
    }

    BoundingBox boundingBox() const override {
        return {this->width, this->height};
    }
};

// Класс Квадрат (наследуется от Прямоугольника для элегантности иерархии)
class Square : public Rectangle {
public:
    Square(double centerX, double centerY, Color color, double edgeLength) 
        : Rectangle(centerX, centerY, color, edgeLength, edgeLength) {}
};

// Класс Равносторонний Треугольник
class Triangle : public Shape {
private:
    double edgeLength = 0.0;

public:
    Triangle(double centerX, double centerY, Color color, double edgeLength) 
        : Shape(centerX, centerY, color) {
        this->edgeLength = edgeLength;
    }

    double area() const override {
        // Формула площади треугольника 
        return this->edgeLength * this->edgeLength * std::sqrt(3.0) / 4.0;
    }

    BoundingBox boundingBox() const override {
        // Описывающий прямоугольник: ширина равна стороне, высота равна высоте треугольника
        double h = this->edgeLength * std::sqrt(3.0) / 2.0;
        return {this->edgeLength, h};
    }
};

int main() {
    std::cout << "=== Иерархия геометрических фигур ===\n";
    std::cout << "Доступные фигуры: circle, square, triangle, rectangle, exit\n";

    std::string command;
    while (true) {
        std::cout << "\nВведите команду фигуры: ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        double x, y;
        int colorNum;
        std::cout << "Введите координаты центра X и Y: ";
        std::cin >> x >> y;
        std::cout << "Выберите цвет (0-None, 1-Red, 2-Blue, 3-Green): ";
        std::cin >> colorNum;
        Color figColor = static_cast<Color>(colorNum);

        Shape* shape = nullptr;

        if (command == "circle") {
            double r;
            std::cout << "Введите радиус: ";
            std::cin >> r;
            shape = new Circle(x, y, figColor, r);
        } 
        else if (command == "square") {
            double a;
            std::cout << "Введите длину ребра: ";
            std::cin >> a;
            shape = new Square(x, y, figColor, a);
        } 
        else if (command == "triangle") {
            double a;
            std::cout << "Введите длину стороны треугольника: ";
            std::cin >> a;
            shape = new Triangle(x, y, figColor, a);
        } 
        else if (command == "rectangle") {
            double w, h;
            std::cout << "Введите ширину и высоту: ";
            std::cin >> w >> h;
            shape = new Rectangle(x, y, figColor, w, h);
        } 
        else {
            std::cout << "Ошибка: Неизвестная фигура.\n";
            continue;
        }

        if (shape != nullptr) {
            std::cout << "--- Результаты расчёта ---\n";
            std::cout << "Площадь фигуры: " << shape->area() << "\n";
            BoundingBox box = shape->boundingBox();
            std::cout << "Описывающий прямоугольник: " << box.width << " x " << box.height << "\n";
            
            delete shape; // Освобождаем динамическую память
        }
    }

    return 0;
}
