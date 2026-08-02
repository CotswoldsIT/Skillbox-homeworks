#include <iostream>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Функция поиска подстроки по указателям на char согласно чек-листу
bool substr(const char* a, const char* b) {
    // Если подстрока пустая, она всегда является подстрокой
    if (*b == '\0') return true;

    // Внешний цикл идет по основной строке a
    for (int i = 0; *(a + i) != '\0'; ++i) {
        int j = 0;
        
        // Внутренний цикл сравнивает символы, пока b не кончится или не будет несовпадения
        while (*(b + j) != '\0' && *(a + i + j) != '\0' && *(a + i + j) == *(b + j)) {
            ++j;
        }
        
        // Если дошли до конца строки b, значит подстрока полностью совпала
        if (*(b + j) == '\0') {
            return true;
        }
    }
    
    return false;
}

int main() {
    const char* a = "Hello world";
    const char* b = "wor";
    const char* c = "banana";

    std::cout << "=== Поиск подстроки через указатели ===\n";
    std::cout << "Строка: \"" << a << "\"\n";
    
    std::cout << "Ищем \"" << b << "\": " << (substr(a, b) ? "true (Найдено)" : "false (Не найдено)") << "\n";
    std::cout << "Ищем \"" << c << "\": " << (substr(a, c) ? "true (Найдено)" : "false (Не найдено)") << "\n";

    return 0;
}
