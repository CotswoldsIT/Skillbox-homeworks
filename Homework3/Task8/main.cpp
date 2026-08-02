#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int salary1 = 0;
    int salary2 = 0;
    int salary3 = 0;

    // Ввод данных
    std::cout << "=== Расчёт параметров зарплат отдела ===\n";
    std::cout << "Введите зарплату первого сотрудника: ";
    std::cin >> salary1;
    std::cout << "Введите зарплату второго сотрудника: ";
    std::cin >> salary2;
    std::cout << "Введите зарплату третьего сотрудника: ";
    std::cin >> salary3;

    std::cout << "-----Считаем-----\n";

    //  поиск максимума и минимума
    int maxSalary = salary1;
    int minSalary = salary1;

    // Ищем максимум
    if (salary2 > maxSalary) maxSalary = salary2;
    if (salary3 > maxSalary) maxSalary = salary3;

    // Ищем минимум
    if (salary2 < minSalary) minSalary = salary2;
    if (salary3 < minSalary) minSalary = salary3;

    // Расчет разницы и среднего арифметического
    int salaryDifference = maxSalary - minSalary;
    int averageSalary = (salary1 + salary2 + salary3) / 3;

    // Вывод результатов строго по формату задания
    std::cout << "Самая высокая зарплата в отделе: " << maxSalary << " рублей\n";
    std::cout << "Разница между самой высокой и самой низкой зарплатой в отделе: " << salaryDifference << " рублей\n";
    std::cout << "Средняя зарплата в отделе: " << averageSalary << " рублей\n";

    return 0;
}
