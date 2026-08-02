#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <clocale>   
#include <windows.h> // Нужен для точной настройки кодировки  

// Настройка русского языка
auto locale_init = []() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(65001);       
    SetConsoleOutputCP(65001); 
    return 0;
}();

// Мьютексы для синхронизации
std::mutex station_mutex; // Защищает единственное место на вокзале
std::mutex cout_mutex;    // Защищает вывод в консоль от перемешивания букв

// Функция для обновления экрана, чтобы приглашение к вводу всегда было внизу
void print_station_status(const std::string& message, char current_train = ' ') {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << message << "\n";
    if (current_train != ' ') {
        std::cout << "-> [Диспетчер]: Чтобы отправить поезд [" << current_train << "], введите цифру 1: ";
    }
}

// Функция движения поезда 
void train_route(char train_name, int travel_time) {
    // 1. Имитируем время поезда в пути до вокзала
    std::this_thread::sleep_for(std::chrono::seconds(travel_time));

    // Поезд доехал до вокзала и сообщает об этом, не ломая чужой ввод
    print_station_status("[Информация] Поезд [" + std::string(1, train_name) + "] подошёл к вокзалу и ожидает свободного места.");

    // 2. Поезд пытается занять платформу (ждёт, если занято другим поездом)
    station_mutex.lock(); 

    // Платформа свободна, поезд прибыл
    print_station_status("\n[!] Поезд [" + std::string(1, train_name) + "] ПРИБЫЛ на вокзал и занял платформу.", train_name);

    // 3. Ожидаем команду отбытия именно для этого поезда
    std::string command;
    while (true) {
        std::cin >> command;
        if (command == "1") {
            break;
        }
        // Если ввели не то, вежливо напоминаем команду
        print_station_status("[Ошибка] Неизвестная команда.", train_name);
    }

    // Поезд уезжает с вокзала
    print_station_status("Поезд [" + std::string(1, train_name) + "] ОТБЫЛ с вокзала. Путь свободен.\n");

    // Освобождаем платформу вокзала для других поездов в очереди
    station_mutex.unlock(); 
}

int main() {
    const int train_count = 3;
    char names[train_count] = {'A', 'B', 'C'};
    int travel_times[train_count];

    // Сбор данных от пользователя
    std::cout << "=== Расписание движения поездов ===\n";
    for (int i = 0; i < train_count; ++i) {
        std::cout << "Введите время в пути для поезда [" << names[i] << "] (в секундах): ";
        std::cin >> travel_times[i];
    }

    std::cout << "\n=== ПОЕЗДА НАЧАЛИ ДВИЖЕНИЕ ===\n";
    std::vector<std::thread> threads;

    // Запускаем каждый поезд в отдельном потоке 
    for (int i = 0; i < train_count; ++i) {
        threads.push_back(std::thread(train_route, names[i], travel_times[i]));
    }

    // ждём, пока все 3 поезда завершат свои маршруты и уедут
    for (int i = 0; i < train_count; ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    std::cout << "Все три поезда успешно обработаны. Работа вокзала завершена.\n";
    return 0;
}
