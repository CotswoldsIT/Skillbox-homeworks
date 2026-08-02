#include <iostream>
#include <vector>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция обмена значений между вектором и массивом по чек-листу
void swapvec(std::vector<int>& vec, int* arr) {
    for (size_t i = 0; i < vec.size(); ++i) {
        int temp = vec[i];
        vec[i] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    std::vector<int> a = {1, 2, 3, 4};
    int b[] = {2, 4, 6, 8};

    std::cout << "=== Обмен значений между вектором и массивом ===\n";

    // Вызываем функцию обмена
    swapvec(a, b);

    // Выводим изменённый вектор
    std::cout << "Элементы вектора A после обмена: ";
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    // Выводим изменённый массив
    std::cout << "Элементы массива B после обмена: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
