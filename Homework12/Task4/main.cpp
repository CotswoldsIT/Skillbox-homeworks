#include <iostream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Перечисление нот в виде битовых масок по ТЗ
enum note {
    DO = 1,
    RE = 2,
    MI = 4,
    FA = 8,
    SOL = 16,
    LA = 32,
    SI = 64
};

int main() {
    std::string chord_input;

    std::cout << "=== Механическое пианино ===\n";
    std::cout << "Введите аккорд (цифры от 1 до 7 без пробелов, например 123 или 1357):\n";
    std::cin >> chord_input;

    int notes_mask = 0; // Переменная для хранения итоговой битовой маски

    // Формируем битовую маску аккорда
    for (int i = 0; i < chord_input.length(); ++i) {
        char ch = chord_input[i];

        // Проверяем, что введены корректные цифры клавиш от '1' до '7'
        if (ch >= '1' && ch <= '7') {
            int note_index = ch - '1'; // Переводим символ в индекс от 0 до 6
            notes_mask |= (1 << note_index); // Выставляем бит для конкретной ноты
        }
    }

    std::cout << "\nЗвучит аккорд: ";

    // Проверяем наличие битов для каждой ноты и выводим результат по ТЗ
    if (notes_mask & DO)  std::cout << "DO ";
    if (notes_mask & RE)  std::cout << "RE ";
    if (notes_mask & MI)  std::cout << "MI ";
    if (notes_mask & FA)  std::cout << "FA ";
    if (notes_mask & SOL) std::cout << "SOL ";
    if (notes_mask & LA)  std::cout << "LA ";
    if (notes_mask & SI)  std::cout << "SI ";
    
    std::cout << "\n";

    return 0;
}
