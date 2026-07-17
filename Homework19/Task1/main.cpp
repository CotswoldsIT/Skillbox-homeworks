#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

struct Task {
    std::string name;
    double duration = 0.0; // Время выполнения в секундах
};

int main() {
    std::vector<Task> finished_tasks;
    std::string current_task = "";
    std::time_t start_time = 0;

    std::cout << "=== Менеджер учёта времени ===\n";
    std::cout << "Доступные команды: begin, end, status, exit\n\n";

    std::string command;
    while (true) {
        std::cout << "Введите команду: ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Программа завершена.\n";
            break;
        }

        if (command == "begin") {
            // автоматическое завершение выполненной задачи
            if (!current_task.empty()) {
                std::time_t end_time = std::time(nullptr);
                double diff = std::difftime(end_time, start_time);
                
                // Ищем, была ли уже такая задача раньше, чтобы суммировать время
                bool found = false;
                for (auto& task : finished_tasks) {
                    if (task.name == current_task) {
                        task.duration += diff;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    finished_tasks.push_back({current_task, diff});
                }
                std::cout << "Задача \"" << current_task << "\" автоматически завершена.\n";
            }

            // Начинаем новую задачу
            std::cout << "Введите название новой задачи: ";
            std::cin >> current_task;
            start_time = std::time(nullptr);
            std::cout << "Начато отслеживание задачи: " << current_task << "\n";
        }
        else if (command == "end") {
            if (current_task.empty()) {
                std::cout << "Сейчас нет активных задач.\n";
            } else {
                std::time_t end_time = std::time(nullptr);
                double diff = std::difftime(end_time, start_time);

                bool found = false;
                for (auto& task : finished_tasks) {
                    if (task.name == current_task) {
                        task.duration += diff;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    finished_tasks.push_back({current_task, diff});
                }

                std::cout << "Задача \"" << current_task << "\" успешно завершена.\n";
                current_task = ""; // Сбрасываем активную задачу
            }
        }
        else if (command == "status") {
            std::cout << "\n--- СТАТУС УЧЁТА ВРЕМЕНИ ---\n";
            if (finished_tasks.empty()) {
                std::cout << "Завершённых задач пока нет.\n";
            } else {
                std::cout << "Завершённые задачи:\n";
                for (const auto& task : finished_tasks) {
                    // Переводим секунды в часы 
                    double hours = task.duration / 3600.0;
                    std::cout << " - " << task.name << ": " << task.duration 
                              << " сек. (~" << hours << " ч.)\n";
                }
            }

            if (!current_task.empty()) {
                std::time_t current_now = std::time(nullptr);
                double current_diff = std::difftime(current_now, start_time);
                std::cout << "Текущая выполняемая задача: " << current_task 
                          << " (в работе " << current_diff << " сек.)\n";
            } else {
                std::cout << "Нет текущей выполняемой задачи.\n";
            }
            std::cout << "----------------------------\n\n";
        }
        else {
            std::cout << "Ошибка: Неизвестная команда.\n";
        }
    }

    return 0;
}
