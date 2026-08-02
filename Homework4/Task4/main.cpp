#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int amount = 0;

    // Текстовый интерфейс: описание и ввод данных
    std::cout << "=== Автоматическая система выдачи купюр банкомата ===\n";
    std::cout << "Введите сумму для снятия (руб.): ";
    std::cin >> amount;

    std::cout << "-----Проверяем-----\n";

    // 1. Проверка на некорректный ввод и лимит в 150 000 рублей
    if (amount <= 0) {
        std::cout << "Ошибка! Сумма должна быть больше нуля.\n";
        return 1;
    }
    if (amount > 150000) {
        std::cout << "Ошибка! Банкомат не может выдать более 150 000 рублей за один раз.\n";
        return 1;
    }

    // 2. Проверка на кратность минимальной купюре (100 рублей)
    if (amount % 100 != 0) {
        std::cout << "Ошибка! Выдать ровно " << amount << " руб. невозможно. Сумма должна быть кратна 100 руб.\n";
        return 1;
    }

    // Переменные для подсчета количества купюр каждого номинала
    int note5000 = 0, note2000 = 0, note1000 = 0;
    int note500 = 0, note200 = 0, note100 = 0;

    // Временная переменная для остатка суммы в процессе расчета
    int remainingAmount = amount;

    // 3. Жадный алгоритм расчета купюр от крупных к мелким
    note5000 = remainingAmount / 5000;
    remainingAmount %= 5000;

    note2000 = remainingAmount / 2000;
    remainingAmount %= 2000;

    note1000 = remainingAmount / 1000;
    remainingAmount %= 1000;

    note500 = remainingAmount / 500;
    remainingAmount %= 500;

    note200 = remainingAmount / 200;
    remainingAmount %= 200;

    note100 = remainingAmount / 100;

    // 4. Вывод результатов (показываем только те номиналы, которые выдаются)
    std::cout << "Сумма " << amount << " руб. будет выдана следующими купюрами:\n";
    
    if (note5000 > 0) std::cout << "- Купюр по 5 000 руб.: " << note5000 << " шт.\n";
    if (note2000 > 0) std::cout << "- Купюр по 2 000 руб.: " << note2000 << " шт.\n";
    if (note1000 > 0) std::cout << "- Купюр по 1 000 руб.: " << note1000 << " шт.\n";
    if (note500 > 0)  std::cout << "- Купюр по 500 руб.: " << note500 << " шт.\n";
    if (note200 > 0)  std::cout << "- Купюр по 200 руб.: " << note200 << " шт.\n";
    if (note100 > 0)  std::cout << "- Купюр по 100 руб.: " << note100 << " шт.\n";

    std::cout << "--------------------------------------------------------\n";
    return 0;
}
