#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <limits>
#include <windows.h> 

// Настройка русского языка для Windows консоли (UTF-8)
auto locale_init_in = SetConsoleCP(65001);
auto locale_init_out = SetConsoleOutputCP(65001);

// Класс Рыбы (будет использоваться как тип исключения)
class Fish {};

// Класс Сапога (будет использоваться как тип исключения)
class Boot {};

// Структура сектора игрового поля
struct Sector {
    bool hasFish = false;
    bool hasBoot = false;
};

int main() {
    // Инициализация генератора случайных чисел 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Создаем пруд из 9 секторов
    std::vector<Sector> field(9);

    // Случайное размещение рыбы
    int fishPos = std::rand() % 9;
    field[fishPos].hasFish = true;

    // Случайное размещение 3 сапогoв (строго в разные свободные сектора)
    int bootsPlaced = 0;
    while (bootsPlaced < 3) {
        int bootPos = std::rand() % 9;
        // Сапог и рыба не могут быть в одном секторе, и сапоги не должны накладываться
        if (!field[bootPos].hasFish && !field[bootPos].hasBoot) {
            field[bootPos].hasBoot = true;
            bootsPlaced++;
        }
    }

    std::cout << "=== ИГРА ПО ЛОВЛЕ РЫБЫ ===\n";
    std::cout << "Перед вами условный пруд из 9 секторов (номера от 0 до 8).\n";
    std::cout << "Где-то там плавает 1 рыба и притаились 3 старых сапога.\n";
    std::cout << "Закидывайте удочку!\n\n";

    int attempts = 0;

    while (true) {
        std::cout << "Введите номер сектора для заброса удочки (0-8): ";
        int sector;

        if (!(std::cin >> sector)) {
            std::cout << "Ошибка! Введите корректное целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (sector < 0 || sector > 8) {
            std::cout << "Ошибка! Сектор должен быть строго от 0 до 8. Попробуйте снова.\n";
            continue;
        }

        attempts++;

        try {
            // Проверяем содержимое сектора и выбрасываем соответствующий тип данных
            if (field[sector].hasFish) {
                throw Fish(); //   пользовательское исключение рыбы
            } 
            else if (field[sector].hasBoot) {
                throw Boot(); //   пользовательское исключение сапога
            } 
            else {
                std::cout << "Сектор пустой. Рыба не клюет. Закидываем удочку повторно!\n\n";
            }
        } 
        catch (const Fish& e) {
            std::cout << "\n=========================================\n";
            std::cout << "УРА! Вы успешно поймали рыбу! Празднуем победу!\n";
            std::cout << "Количество потраченных попыток: " << attempts << "\n";
            std::cout << "=========================================\n";
            break; // Завершаем программу
        } 
        catch (const Boot& e) {
            std::cout << "\n=========================================\n";
            std::cout << "УВЫ... Вы поймали старый сапог! Рыбалка не удалась.\n";
            std::cout << "Игра завершена с отрицательным результатом.\n";
            std::cout << "=========================================\n";
            break; // Завершаем программу
        }
    }

    return 0;
}
