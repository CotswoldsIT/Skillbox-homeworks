#include <iostream>
#include <string>
#include <map>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

int main() {
    // Словарь для хранения очереди: фамилия -> количество людей
    std::map<std::string, int> registry_queue;

    std::cout << "=== Программа «Регистратура» ===\n";
    std::cout << "Вводите фамилии пациентов или команду 'Next'.\n";
    std::cout << "Введите 'exit' для завершения работы.\n\n";

    std::string input;
    while (true) {
        std::cout << "← ";
        std::cin >> input;

        if (input == "exit") {
            break;
        }

        if (input == "Next") {
            // Если очередь пуста, выводить некого
            if (registry_queue.empty()) {
                std::cout << "→ Очередь пуста.\n";
            } else {
                // Итератор на первый элемент (он всегда первый по алфавиту за O(1))
                auto first_patient = registry_queue.begin();
                
                std::cout << "→ " << first_patient->first << "\n";

                // Уменьшаем количество людей с этой фамилией
                first_patient->second--;

                // Если людей с такой фамилией больше нет, удаляем элемент из карты за O(log n)
                if (first_patient->second == 0) {
                    registry_queue.erase(first_patient);
                }
            }
        } else {
            // Добавляем пациента в очередь или увеличиваем счётчик за O(log n)
            registry_queue[input]++;
        }
    }

    return 0;
}
