#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция обмена значений по указателям согласно чек-листу
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 10;
    int b = 20;

    std::cout << "=== Обмен значений через указатели ===\n";
    std::cout << "Значения до обмена: a = " << a << ", b = " << b << "\n";

    // Передаем адреса переменных в функцию
    swap(&a, &b);

    std::cout << "Значения после обмена: a = " << a << ", b = " << b << "\n";

    return 0;
}
