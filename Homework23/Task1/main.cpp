#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm> 
#include <clocale>   
#include <windows.h> // Нужен для точной настройки кодировки в Windows

// Настройка русского языка 
auto locale_init = []() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    SetConsoleCP(65001);       // UTF-8 на ввод (чтобы cin читал русские буквы)
    SetConsoleOutputCP(65001); // UTF-8 на вывод (чтобы cout не ломал строки)
    return 0;
}();

// сохранение результатов заплыва
struct Result {
    std::string name;
    double time;
};

// запись данных финишировавших
std::vector<Result> leaderboard; 


std::mutex cout_mutex;   // Чтобы строчки в консоли не перекрывали друг друга
std::mutex result_mutex; // Чтобы потоки не сломали вектор leaderboard при записи

// Функция, которую выполняет каждый пловец в отдельном потоке
void swimmer_route(std::string name, double speed) {
    double distance = 0.0;
    double time = 0.0;

    // Плывем, пока дистанция меньше 100 метров
    while (distance < 100.0) {
        // Имитируем заплыв: ждем 1 секунду реального времени
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time += 1.0;
        distance += speed;

        if (distance > 100.0) {
            distance = 100.0;
        }

        // Блокируем консоль мьютексом, чтобы текст от разных потоков не перемешивался
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << name << " проплыл " << distance << " метров.\n";
    }

    // Запись результата на финише 
    std::lock_guard<std::mutex> lock(result_mutex);
    leaderboard.push_back({name, time});
    std::cout << "!!! Пловец " << name << " ФИНИШИРОВАЛ за " << time << " сек. !!!\n";
}

int main() {
    const int swimmers_count = 6;
    std::vector<std::string> names(swimmers_count);
    std::vector<double> speeds(swimmers_count);

    // 1. Сбор данных
    std::cout << "=== Регистрация участников заплыва ===\n";
    for (int i = 0; i < swimmers_count; ++i) {
        std::cout << "Введите имя " << i + 1 << "-го пловца: ";
        std::cin >> names[i];
        std::cout << "Введите его скорость (м/с): ";
        std::cin >> speeds[i];
    }

    // 2. Создание и запуск потоков 
    std::vector<std::thread> threads;
    std::cout << "\n=== СТАРТ ЗАПЛЫВА ===\n";
    for (int i = 0; i < swimmers_count; ++i) {
        threads.push_back(std::thread(swimmer_route, names[i], speeds[i]));
    }

    // 3. Ожидание финиша всех участников 
    for (int i = 0; i < swimmers_count; ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    // 4. Сортировка таблицы по возрастанию времени
    std::sort(leaderboard.begin(), leaderboard.end(), [](const Result& a, const Result& b) {
        return a.time < b.time;
    });

    // 5. Вывод таблицы лидеров
    std::cout << "\n=== ИТОГОВЫЙ ПРОТОКОЛ (ТАБЛИЦА ЛИДЕРОВ) ===\n";
    for (size_t i = 0; i < leaderboard.size(); ++i) {
        std::cout << i + 1 << " место: " << leaderboard[i].name 
                  << " — " << leaderboard[i].time << " сек.\n";
    }

    return 0;
}
