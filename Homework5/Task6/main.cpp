#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int startDeposit = 0;
    int percentRate = 0;
    int targetAmount = 0;

    // Текстовый интерфейс: описание и ввод данных
    std::cout << "=== Калькулятор капитализации вклада ===\n";
    std::cout << "Введите размер вклада (руб.): ";
    std::cin >> startDeposit;
    std::cout << "Введите процентную ставку (%): ";
    std::cin >> percentRate;
    std::cout << "Введите желаемую сумму (руб.): ";
    std::cin >> targetAmount;

    // 1. Контроль ввода от зацикливания и зависания
    if (startDeposit <= 0 || percentRate <= 0 || targetAmount <= 0) {
        std::cout << "Ошибка! Все введенные значения должны быть строго больше нуля.\n";
        return 1;
    }
    if (targetAmount <= startDeposit) {
        std::cout << "Вы уже достигли желаемой суммы! Ждать не нужно: 0 лет.\n";
        return 0;
    }

    std::cout << "-----Считаем-----\n";

    int currentDeposit = startDeposit;
    int yearsCount = 0;

    // 2. Цикл расчета капитализации по годам в целых числах
    while (currentDeposit < targetAmount) {
        // Начисляем процент и за счет целочисленной математики C++ отбрасываем копейки
        currentDeposit = currentDeposit + (currentDeposit * percentRate / 100);
        yearsCount++;
    }

    // Вывод результата
    std::cout << "Придётся подождать: " << yearsCount << " лет.\n";
    std::cout << "Итоговая сумма на счете составит: " << currentDeposit << " руб.\n";

    return 0;
}
