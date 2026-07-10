#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    float totalSize = 0.0f;
    float downloadSpeed = 0.0f;

    std::cout << "Укажите размер файла для скачивания (МБ): ";
    std::cin >> totalSize;
    std::cout << "Какова скорость вашего соединения? (МБ/с): ";
    std::cin >> downloadSpeed;

    // Контроль ввода
    if (totalSize <= 0.0f || downloadSpeed <= 0.0f) {
        std::cout << "Ошибка! Размер файла и скорость соединения должны быть больше нуля.\n";
        return 1;
    }

    float downloaded = 0.0f;
    int seconds = 0;

    std::cout << "\nВывод:\n";

    // Цикл скачивания по секундам
    while (downloaded < totalSize) {
        seconds++;
        downloaded += downloadSpeed;

        // Если накачали больше, чем весит файл, приравниваем к максимуму
        if (downloaded > totalSize) {
            downloaded = totalSize;
        }

        // Считаем проценты в целых числах
        int percent = static_cast<int>((downloaded * 100.0f) / totalSize);

        std::cout << "Прошло " << seconds << " сек. Скачано " 
                  << downloaded << " из " << totalSize << " МБ (" << percent << "%).\n";
    }

    std::cout << "\nСкачивание завершено. Всего прошло секунд: " << seconds << "\n";

    return 0;
}
