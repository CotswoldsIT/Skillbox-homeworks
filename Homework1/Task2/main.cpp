#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    // Переменные со значениями
    int productPrice = 1200;  // Стоимость товара
    int deliveryPrice = 350;  // Стоимость доставки
    int discountAmount = 150; // Скидка

    // Формула расчет полной стоимости
    int totalPrice = productPrice + deliveryPrice - discountAmount;

    // Имитация ввода данных 
    std::cout << "--- Калькулятор стоимости товара ---\n";
    
    std::cout << "Введите стоимость товара: " << productPrice << "\n";
    std::cout << "Введите стоимость доставки: " << deliveryPrice << "\n";
    std::cout << "Введите скидку на товар: " << discountAmount << "\n";
    
    // Вывод результата
    std::cout << "------------------------------------\n";
    std::cout << "Полная стоимость к оплате: " << totalPrice << " руб.\n";

    return 0;
}


