#include <iostream>
#include <ctime>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    std::cout << "=== Программа «Точный таймер» ===\n";

    int input_minutes = 0;
    int input_seconds = 0;

    std::cout << "Введите минуты: ";
    std::cin >> input_minutes;
    std::cout << "Введите секунды: ";
    std::cin >> input_seconds;

    if (input_minutes < 0 || input_seconds < 0) {
        std::cout << "Ошибка: Время не может быть отрицательным!\n";
        return 1;
    }

    // Переводим всё в общее количество секунд
    int total_delay_seconds = (input_minutes * 60) + input_seconds;

    // Вычисляем целевое время остановки таймера 
    std::time_t start_time = std::time(nullptr);
    std::time_t target_time = start_time + total_delay_seconds;

    std::cout << "\nТаймер запущен на " << input_minutes << " мин. " << input_seconds << " сек.\n";

    int last_displayed_seconds = -1;

    // Цикл обратного отсчёта
    while (true) {
        std::time_t now = std::time(nullptr);
        
        // Вычисляем, сколько секунд осталось до цели
        double seconds_left = std::difftime(target_time, now);

        // Если время вышло — останавливаем цикл
        if (seconds_left <= 0) {
            break;
        }

        // Обновляем экран только если изменилась секунда, чтобы не спамить в консоль
        if (static_cast<int>(seconds_left) != last_displayed_seconds) {
            last_displayed_seconds = static_cast<int>(seconds_left);

            int display_minutes = last_displayed_seconds / 60;
            int display_seconds = last_displayed_seconds % 60;

            // Выводим оставшееся время в формате: минуты и секунды
            std::cout << "Осталось времени: " << display_minutes << " мин. " << display_seconds << " сек.\n";
        }
    }

    // Финал 
    std::cout << "\n🔔 DING! DING! DING! Время вышло!\n";

    return 0;
}
