#include <iostream>
#include <cmath>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Размеры исходного бруска
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    std::cout << "Введите размеры бруска:\n";
    std::cout << "X: ";
    std::cin >> x;
    std::cout << "Y: ";
    std::cin >> y;
    std::cout << "Z: ";
    std::cin >> z;

    // Контроль ввода: размеры должны быть не меньше размера одного кубика (5 см)
    if (x < 5.0f || y < 5.0f || z < 5.0f) {
        std::cout << "Ошибка! Минимальный размер бруска — 5x5x5 см.\n";
        return 1;
    }

    // Считаем сколько кубиков помещается по каждой стороне (отбрасывая дроби)
    int countX = static_cast<int>(x / 5.0f);
    int countY = static_cast<int>(y / 5.0f);
    int countZ = static_cast<int>(z / 5.0f);

    // Общее количество цельных кубиков
    int totalCubes = countX * countY * countZ;

    std::cout << "\nВывод:\n";
    std::cout << "Из этого бруска можно изготовить " << totalCubes << " кубиков.\n";

    // Поиск максимального размера набора кубов (начиная с 2x2x2 = 8 кубиков)
    int maxSetCubes = 0;
    int size = 2;

    while (true) {
        int currentCubeVolume = size * size * size;
        
        // Если кубический объем укладывается в наше общее число деталей
        if (currentCubeVolume <= totalCubes) {
            maxSetCubes = currentCubeVolume;
            size++;
        } else {
            break;
        }
    }

    // Если нашли набор, который не меньше минимальных 8 кубиков
    if (maxSetCubes >= 8) {
        std::cout << "Из них можно составить набор из " << maxSetCubes << " кубиков.\n";
    } else {
        std::cout << "Из этого количества кубиков нельзя составить торговый набор.\n";
    }

    return 0;
}
