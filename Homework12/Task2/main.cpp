#include <iostream>
#include <string>

// Настройка русского языка 
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::string personal_part;
    std::string fractional_part;

    std::cout << "=== Сшиватель дробных чисел ===\n";
    
    std::cout << "Введите целую часть числа: ";
    std::cin >> personal_part;
    
    std::cout << "Введите дробную часть числа: ";
    std::cin >> fractional_part;

    // В русской локали разделитель — запятая, склеиваем через неё
    std::string full_number_str = personal_part + "," + fractional_part;

    // Преобразуем получившуюся строку в тип double
    double result_number = std::stod(full_number_str);

    std::cout << "Полученное число с плавающей точкой (double): " << result_number << "\n";

    return 0;
}
