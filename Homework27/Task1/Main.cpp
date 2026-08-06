#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <limits>
#include <windows.h> 

// Настройка русского языка для Windows консоли (UTF-8)
auto locale_init_in = SetConsoleCP(65001);
auto locale_init_out = SetConsoleOutputCP(65001);

// Функция для наглядного отображения склада и корзины пользователю
void printStatus(const std::map<std::string, int>& shop, const std::map<std::string, int>& cart) {
    std::cout << "\n=========================================\n";
    std::cout << "--- ТЕКУЩИЙ СКЛАД МАГАЗИНА ---\n";
    if (shop.empty()) {
        std::cout << "  [На складе пусто]\n";
    } else {
        for (const auto& [art, count] : shop) {
            std::cout << "  " << art << ": " << count << " шт.\n";
        }
    }
    std::cout << "--- СОДЕРЖИМОЕ ВАШЕЙ КОРЗИНЫ ---\n";
    if (cart.empty()) {
        std::cout << "  [Корзина пуста]\n";
    } else {
        for (const auto& [art, count] : cart) {
            std::cout << "  " << art << ": " << count << " шт.\n";
        }
    }
    std::cout << "=========================================\n";
}

int main() {
    std::map<std::string, int> shopDatabase;
    std::map<std::string, int> shoppingCart;

    std::cout << "=== ЭТАП 1: ЗАПОЛНЕНИЕ БАЗЫ ДАННЫХ МАГАЗИНА ===\n";
    std::cout << "Вводите название товара и его количество через пробел в одну строку.\n";
    std::cout << "Пример ввода: Молоко 10\n";
    std::cout << "Чтобы закончить заполнение склада, введите: end 0\n\n";
    
    while (true) {
        std::string article;
        int count;
        std::cout << "Введите товар и количество: ";
        
        if (!(std::cin >> article >> count)) {
            std::cout << "Ошибка! Неверный формат склада. Вводите строго: [Название] [Количество] (например: Хлеб 5).\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (article == "end" || article == "End" || article == "END") {
            break;
        }
        
        if (count < 0) {
            std::cout << "Ошибка! Количество не может быть отрицательным. Попробуйте снова.\n";
            continue;
        }
        
        shopDatabase[article] += count;
    }

    // Очищаем буфер после завершения ввода базы данных
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n=== ЭТАП 2: РАБОТА С КОРЗИНОЙ ===\n";
    std::cout << "Теперь вы можете добавлять или удалять товары со склада.\n";
    std::cout << "ПРАВИЛА ВВОДА КОМАНД:\n";
    std::cout << "  -> Чтобы добавить товар, пишите: add Название Количество  (Пример: add Молоко 3)\n";
    std::cout << "  -> Чтобы удалить товар, пишите:  remove Название Количество  (Пример: remove Молоко 1)\n";
    std::cout << "  -> Чтобы выйти из программы, пишите: exit\n";

    while (true) {
        printStatus(shopDatabase, shoppingCart);
        
        std::string command;
        std::cout << "Введите команду по шаблону (например, add Молоко 3): ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        if (command != "add" && command != "remove") {
            std::cout << "Ошибка: Неизвестная команда '" << command << "'!\n";
            std::cout << "Вы должны начать ввод со слова 'add' (добавить) или 'remove' (удалить).\n";
            std::cout << "Шаблон: add [Товар] [Количество] или remove [Товар] [Количество]\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::string article;
        int count;
        
        if (!(std::cin >> article >> count)) {
            std::cout << "Ошибка параметров команды!\n";
            std::cout << "После команды '" << command << "' вы забыли указать название товара или его количество.\n";
            std::cout << "Правильный формат: " << command << " [Название] [Количество] (например: " << command << " Сыр 2)\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            if (count <= 0) {
                throw std::invalid_argument("Количество товара должно быть больше нуля.");
            }

            if (command == "add") {
                if (shopDatabase.find(article) == shopDatabase.end()) {
                    throw std::invalid_argument("Данный товар отсутствует в магазине. Проверьте правильность написания из списка выше.");
                }
                if (shopDatabase[article] < count) {
                    throw std::runtime_error("На складе магазина нет такого количества товара.");
                }

                shopDatabase[article] -= count;
                shoppingCart[article] += count;
                std::cout << "Успешно добавлено в корзину: " << article << " в количестве " << count << " шт.\n";

            } else if (command == "remove") {
                if (shoppingCart.find(article) == shoppingCart.end() || shoppingCart[article] == 0) {
                    throw std::invalid_argument("Этого товара вообще нет в вашей корзине.");
                }
                if (shoppingCart[article] < count) {
                    throw std::runtime_error("В вашей корзине нет такого количества товара.");
                }

                shoppingCart[article] -= count;
                shopDatabase[article] += count;
                
                if (shoppingCart[article] == 0) {
                    shoppingCart.erase(article);
                }
                std::cout << "Успешно удалено из корзины: " << article << " в количестве " << count << " шт.\n";
            }

        } catch (const std::invalid_argument& e) {
            std::cerr << "\n[Критическая ошибка аргумента (invalid_argument)]\nОписание: " << e.what() << "\n";
        } catch (const std::runtime_error& e) {
            std::cerr << "\n[Ошибка времени выполнения (runtime_error)]\nОписание: " << e.what() << "\n";
        }
    }

    std::cout << "Программа завершена. Спасибо за покупки!\n";
    return 0;
}
