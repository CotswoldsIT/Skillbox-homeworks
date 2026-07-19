#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <clocale>   
#include <windows.h> // Нужен для точной настройки кодировки 

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Доступное меню ресторана
const std::vector<std::string> MENU = {"Пицца", "Суп", "Стейк", "Салат", "Суши"};

// Общие ресурсы
std::queue<std::string> order_queue;  // Очередь заказов от официанта кухне
std::vector<std::string> pickup_zone; // Зона выдачи готовых блюд курьеру
int total_deliveries = 0;             // Счетчик успешных доставок

// Мьютексы для защиты данных
std::mutex kitchen_mutex;  // Защищает процесс симуляции готовки и очереди
std::mutex delivery_mutex; // Защищает зону выдачи и счетчик доставок
std::mutex cout_mutex;     // Защищает вывод в консоль от перемешивания текста

// Функция готовки (выполняется в отдельном detached-потоке на каждый заказ)
void cook_dish(std::string dish_name) {
    //  время готовки: 1-2 секунды
    int cook_time = 1 + std::rand() % 2;
    
    std::this_thread::sleep_for(std::chrono::seconds(cook_time));

    // Блюдо готово, переносим его в зону выдачи
    {
        std::lock_guard<std::mutex> lock(delivery_mutex);
        pickup_zone.push_back(dish_name);
    }

    // Выводим сообщение о готовности
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "[Кухня] Блюдо \"" << dish_name << "\" ГОТОВО и передано на выдачу.\n";
    }
}

// Функция работы курьера (выполняется в отдельном независимом потоке)
void courier_worker() {
    while (true) {
        // время приезда курьера: каждые 5 секунд
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::lock_guard<std::mutex> lock(delivery_mutex);
        
        // Если программа уже набрала 10 доставок, курьер завершает работу
        if (total_deliveries >= 10) {
            break;
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "\n---> [Курьер] Приехал курьер забирать готовые заказы. <---\n";
        }

        if (pickup_zone.empty()) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[Курьер] На выдаче пусто. Курьер уехал ни с чем.\n\n";
        } else {
            // Курьер забирает ВСЕ готовые блюда
            int items_taken = 0;
            for (const auto& dish : pickup_zone) {
                total_deliveries++;
                items_taken++;
                
                std::lock_guard<std::mutex> c_lock(cout_mutex);
                std::cout << "[Курьер] Доставлено блюдо: \"" << dish << "\" (Всего доставок: " << total_deliveries << "/10).\n";
                
                if (total_deliveries >= 10) {
                    break;
                }
            }
            pickup_zone.clear(); // Очищаем зону выдачи
            
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[Курьер] Курьер забрал " << items_taken << " зак. и уехал доставлять.\n\n";
        }

        if (total_deliveries >= 10) {
            break;
        }
    }
}

int main() {
    // Включаем поддержку UTF-8 в консоли Windows
    SetConsoleCP(65001);       
    SetConsoleOutputCP(65001); 

    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    std::cout << "=== ОНЛАЙН-РЕСТОРАН НАЧАЛ РАБОТУ ===\n";
    std::cout << "Ожидаем поступления заказов и приезда курьера...\n\n";

    // Запускаем поток курьера
    std::thread courier_thread(courier_worker);

    // Главный цикл: генерация заказов (работает, пока не наберется 10 доставок)
    while (true) {
        // Проверяем условие завершения программы
        {
            std::lock_guard<std::mutex> lock(delivery_mutex);
            if (total_deliveries >= 10) {
                break;
            }
        }

        //  поступление заказов: каждую 1 секунду
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Выбираем случайное блюдо из меню
        std::string new_dish = MENU[std::rand() % MENU.size()];

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[Официант] Поступил новый онлайн-заказ: \"" << new_dish << "\".\n";
        }

        // Передаем заказ на кухню. Сразу запускаем повара в фоне (detach)
        {
            std::lock_guard<std::mutex> lock(kitchen_mutex);
            
            std::lock_guard<std::mutex> c_lock(cout_mutex);
            std::cout << "[Кухня] Повар принял заказ \"" << new_dish << "\" в работу.\n";
            
            //  Запускаем отдельную нить ожидания с вызовом detach для нее
            std::thread cook_thread(cook_dish, new_dish);
            cook_thread.detach(); 
        }
    }

    // Дожидаемся корректного завершения потока курьера
    if (courier_thread.joinable()) {
        courier_thread.join();
    }

    std::cout << "\n=== РЕСТОРАН ВЫПОЛНИЛ 10 ДОСТАВОК И ЗАКРЫЛСЯ ===\n";
    return 0;
}
