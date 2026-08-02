#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string departure, arrival;

    std::cout << "Введите время отправления (HH:MM): ";
    std::cin >> departure;
    std::cout << "Введите время прибытия (HH:MM): ";
    std::cin >> arrival;

    // Проверка формата строки отправления
    if (departure.length() != 5 || departure[2] != ':' ||
        departure[0] < '0' || departure[0] > '9' || departure[1] < '0' || departure[1] > '9' ||
        departure[3] < '0' || departure[3] > '9' || departure[4] < '0' || departure[4] > '9') {
        std::cout << "Ошибка! Некорректный формат времени отправления.\n";
        return 1;
    }

    // Проверка формата строки прибытия
    if (arrival.length() != 5 || arrival[2] != ':' ||
        arrival[0] < '0' || arrival[0] > '9' || arrival[1] < '0' || arrival[1] > '9' ||
        arrival[3] < '0' || arrival[3] > '9' || arrival[4] < '0' || arrival[4] > '9') {
        std::cout << "Ошибка! Некорректный формат времени прибытия.\n";
        return 1;
    }

    // Перевод символов в числа
    int depHours = (departure[0] - '0') * 10 + (departure[1] - '0');
    int depMinutes = (departure[3] - '0') * 10 + (departure[4] - '0');

    int arrHours = (arrival[0] - '0') * 10 + (arrival[1] - '0');
    int arrMinutes = (arrival[3] - '0') * 10 + (arrival[4] - '0');

    // Проверка реальности времени
    if (depHours > 23 || depMinutes > 59 || arrHours > 23 || arrMinutes > 59) {
        std::cout << "Ошибка! Такого времени не существует (часы до 23, минуты до 59).\n";
        return 1;
    }

    // Подсчет в минутах от начала суток
    int depTotalMinutes = depHours * 60 + depMinutes;
    int arrTotalMinutes = arrHours * 60 + arrMinutes;

    // Если прибыли на следующий день
    if (arrTotalMinutes < depTotalMinutes) {
        arrTotalMinutes += 24 * 60;
    }

    // Разница во времени
    int tripMinutes = arrTotalMinutes - depTotalMinutes;

    int resHours = tripMinutes / 60;
    int resMinutes = tripMinutes % 60;

    std::cout << "\nПоездка составила " << resHours << " ч. " << resMinutes << " мин.\n";

    return 0;
}
