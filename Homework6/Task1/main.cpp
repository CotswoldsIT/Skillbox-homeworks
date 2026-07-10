#include <iostream>

int main() {
    // Настройка русского языка для вывода текста
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Стартовые данные по условию задачи
    int totalFood = 100;
    const int monthlyConsumption = 4;

    std::cout << "Всего гречки было на начало подсчёта: " << totalFood << " кг\n";

    // Цикл for выполняется, пока в мешке есть гречка
    int month = 1;
    for (; totalFood > 0; ++month) {
        totalFood -= monthlyConsumption;
        std::cout << "После " << month << " месяца у вас в запасе останется " << totalFood << " кг гречки\n";
    }

    // Сообщение о том, что гречка закончилась (вычитаем 1, так как в конце цикла month увеличился еще раз)
    std::cout << "После " << (month - 1) << " месяца гречка закончится\n";

    return 0;
}
