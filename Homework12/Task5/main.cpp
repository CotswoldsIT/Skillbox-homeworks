#include <iostream>
#include <string>
#include <sstream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Перечисление состояний умного щитка по ТЗ
enum switches {
    LIGHTS_INSIDE = 1,
    LIGHTS_OUTSIDE = 2,
    HEATERS = 4,
    WATER_PIPE_HEATING = 8,
    CONDITIONER = 16
};

int main() {
    int switches_state = 0; // Изначально все приборы выключены

    std::cout << "=== Симулятор Умного Дома (48 часов) ===\n";

    // Цикл симуляции на 2 дня (48 часов)
    for (int hour_total = 0; hour_total < 48; ++hour_total) {
        int current_hour = hour_total % 24;

        // Выводим текущий день и время для удобства
        std::cout << "\n[День " << (hour_total / 24) + 1 << ", Время " 
                  << (current_hour < 10 ? "0" : "") << current_hour << ":00]\n";
        std::cout << "Ввод (Т_внутр Т_внеш Движение(yes/no) Свет(on/off)): ";

        std::string input_line;
        std::getline(std::cin >> std::ws, input_line); // Считываем всю строку целиком

        std::stringstream buffer_stream(input_line);
        float temp_inside, temp_outside;
        std::string movement, lights;

        // Распутываем строку через stringstream по ТЗ
        if (!(buffer_stream >> temp_inside >> temp_outside >> movement >> lights)) {
            std::cout << "Ошибка: Неверный формат ввода параметров датчиков!\n";
            --hour_total; // Повторяем этот же час заново
            continue;
        }

        // Сохраняем предыдущее состояние щитка для отслеживания изменений
        int prev_state = switches_state;

        // 1. Управление обогревом водопровода
        if (temp_outside < 0.0f) {
            switches_state |= WATER_PIPE_HEATING;
        } else if (temp_outside > 5.0f) {
            switches_state &= ~WATER_PIPE_HEATING;
        }

        // 2. Управление садовым освещением (с 16:00 до 5:00 при движении)
        bool is_evening = (current_hour >= 16 || current_hour < 5);
        if (is_evening && movement == "yes") {
            switches_state |= LIGHTS_OUTSIDE;
        } else {
            switches_state &= ~LIGHTS_OUTSIDE;
        }

        // 3. Управление отоплением дома
        if (temp_inside < 22.0f) {
            switches_state |= HEATERS;
        } else if (temp_inside >= 25.0f) {
            switches_state &= ~HEATERS;
        }

        // 4. Управление кондиционером
        if (temp_inside >= 30.0f) {
            switches_state |= CONDITIONER;
        } else if (temp_inside <= 25.0f) {
            switches_state &= ~CONDITIONER;
        }

        // 5. Управление внутренним освещением
        if (lights == "on") {
            switches_state |= LIGHTS_INSIDE;
        } else {
            switches_state &= ~LIGHTS_INSIDE;
        }

        // --- ВЫВОД ИЗМЕНЕНИЙ В КОНСОЛЬ ---
        
        // Обогрев скважины
        if ((switches_state & WATER_PIPE_HEATING) != (prev_state & WATER_PIPE_HEATING)) {
            std::cout << "Обогрев водопровода: " << ((switches_state & WATER_PIPE_HEATING) ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН") << "!\n";
        }
        // Садовый свет
        if ((switches_state & LIGHTS_OUTSIDE) != (prev_state & LIGHTS_OUTSIDE)) {
            std::cout << "Наружный свет в саду: " << ((switches_state & LIGHTS_OUTSIDE) ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН") << "!\n";
        }
        // Отопление дома
        if ((switches_state & HEATERS) != (prev_state & HEATERS)) {
            std::cout << "Отопление в помещении: " << ((switches_state & HEATERS) ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН") << "!\n";
        }
        // Кондиционер
        if ((switches_state & CONDITIONER) != (prev_state & CONDITIONER)) {
            std::cout << "Кондиционер: " << ((switches_state & CONDITIONER) ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН") << "!\n";
        }
        // Внутренний свет
        if ((switches_state & LIGHTS_INSIDE) != (prev_state & LIGHTS_INSIDE)) {
            std::cout << "Свет внутри дома: " << ((switches_state & LIGHTS_INSIDE) ? "ВКЛЮЧЕН" : "ВЫКЛЮЧЕН") << "!\n";
        }

        // Вывод цветовой температуры умных ламп
        if (switches_state & LIGHTS_INSIDE) {
            int color_temp = 5000;
            if (current_hour >= 16 && current_hour <= 20) {
                // Плавное падение с 5000K до 2700K за 4 часа (шаг 575K в час)
                color_temp = 5000 - (current_hour - 16) * 575;
            }
            std::cout << "Цветовая температура освещения: " << color_temp << "K\n";
        }
    }

    std::cout << "\nСимуляция двух дней успешно завершена!\n";
    return 0;
}
