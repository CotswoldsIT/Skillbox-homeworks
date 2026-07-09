#include <iostream>

int main() {
    // Настройка русского языка для вывода текста
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Диапазон
    int minNumber = 0;
    int maxNumber = 63;

    std::cout << "=== Игра «Угадай число» ===\n";
    std::cout << "Загадайте число от " << minNumber << " до " << maxNumber << " в уме.\n";
    std::cout << "Отвечайте на вопросы цифрами: 1 (если ДА) или 0 (если НЕТ).\n\n";

    // Цикл работает, пока границы диапазона не сойдутся в одно число
    while (minNumber < maxNumber) {
        // Середина текущего диапазона
        int mid = minNumber + (maxNumber - minNumber) / 2;
        
        int answer = -1;
        
        // Цикл для контроля ввода (принимаем только цифры 1 или 0)
        while (answer != 1 && answer != 0) {
            std::cout << "Ваше число больше, чем " << mid << "? (1 - да / 0 - нет): ";
            std::cin >> answer;
            
            if (answer != 1 && answer != 0) {
                std::cout << "Ошибка! Введите только 1 (да) или 0 (нет). Попробуйте снова.\n";
                
                // Сброс потока ввода на случай, если случайно ввели букву вместо цифры
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }

        // Сужаем диапазон поиска на основе ответа
        if (answer == 1) {
            minNumber = mid + 1; // Загаданное число строго больше середины
        } else {
            maxNumber = mid;     // Загаданное число меньше или равно середине
        }
    }

    // Когда minNumber станет равен maxNumber, число угадано
    std::cout << "\n--- Игра окончена! ---\n";
    std::cout << "Вы загадали число: " << minNumber << "\n";

    return 0;
}
