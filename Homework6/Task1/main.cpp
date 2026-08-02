#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int totalBuckwheat = 100; // Начальный запас гречки
    const int MONTHLY_EXPENSE = 4; // Расход в месяц

    std::cout << "Всего гречки было на начало подсчёта: " << totalBuckwheat << " кг\n\n";

    // Переменную месяца объявляем ДО цикла, чтобы использовать её в финальном выводе
    int month = 1;

    // Цикл for: стартуем с 1 месяца, уменьшаем гречку на 4 кг на каждом шаге
    for (; totalBuckwheat > 0; month++) {
        totalBuckwheat -= MONTHLY_EXPENSE;
        
        if (totalBuckwheat > 0) {
            std::cout << "После " << month << " месяца у вас в запасе останется " << totalBuckwheat << " кг гречки\n";
        }
    }

    // Так как в конце цикла month увеличился еще раз, вычитаем 1 для точного указания месяца окончания
    std::cout << "После " << (month - 1) << " месяца гречка закончится\n";

    return 0;
}
