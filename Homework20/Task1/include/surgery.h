#pragma once
#include <iostream>
#include <cmath>

// Структура двумерной координаты 
struct Point {
    double x = 0.0;
    double y = 0.0;
};

// Функция ввода координаты
inline Point input_point() {
    Point p;
    std::cout << " (X Y): ";
    std::cin >> p.x >> p.y;
    return p;
}

// Оператор сравнения двух точек для проверки равенства шва и разреза 
inline bool are_equal(const Point& p1, const Point& p2) {
    // Используем небольшую погрешность для double-чисел
    return (std::abs(p1.x - p2.x) < 1e-6) && (std::abs(p1.y - p2.y) < 1e-6);
}

// Функции-инструменты 
inline void use_scalpel(const Point& start, const Point& end) {
    std::cout << "[Скальпель] Сделан разрез от (" << start.x << ", " << start.y 
              << ") до (" << end.x << ", " << end.y << ").\n";
}

inline void use_hemostat(const Point& p) {
    std::cout << "[Зажим] Сделан зажим в точке (" << p.x << ", " << p.y << ").\n";
}

inline void use_tweezers(const Point& p) {
    std::cout << "[Пинцет] Применен пинцет в точке (" << p.x << ", " << p.y << ").\n";
}

inline void use_suture(const Point& start, const Point& end) {
    std::cout << "[Игла] Наложен хирургический шов от (" << start.x << ", " << start.y 
              << ") до (" << end.x << ", " << end.y << ").\n";
}
