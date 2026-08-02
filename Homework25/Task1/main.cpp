#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include <clocale>
#ifdef _WIN32
#include <windows.h> //  для работы с кодовыми страницами Windows
#endif

// Настройка русского языка в консоли
const bool init_locale = []() { 
    std::setlocale(LC_ALL, "ru_RU.UTF-8"); 
#ifdef _WIN32
    SetConsoleCP(65001);       // Устанавливаем кодировку ввода UTF-8 
    SetConsoleOutputCP(65001); // Устанавливаем кодировку вывода UTF-8
#endif
    return true; 
}();

class Toy {
public:
    Toy(const std::string& name) {
        name_ = name;
    }
    std::string getNmae() { //   имя метода 
        return name_;
    }
    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped " << std::endl;
    }
private:
    std::string name_;
};

class Dog {
private:
    std::string name_;
    std::shared_ptr<Toy> toy_;

public:
    Dog(const std::string& name) : name_(name), toy_(nullptr) {}

    void getToy(const std::shared_ptr<Toy>& toy) {
        if (!toy) {
            std::cout << "Эта игрушка еще не создана!" << std::endl;
            return;
        }

        // Если у этой собаки уже есть эта игрушка
        if (toy_ == toy) {
            std::cout << "I already have this toy." << std::endl;
            return;
        }

        // Если игрушка занята другой собакой 
        if (toy.use_count() > 1) {
            std::cout << "Another dog is playing with this toy." << std::endl;
            return;
        }

        // Если игрушка свободна, подбираем её
        toy_ = toy;
        std::cout << name_ << " подобрал игрушку " << toy_->getNmae() << "." << std::endl;
    }

    void dropToy() {
        if (toy_ == nullptr) {
            std::cout << "Nothing to drop." << std::endl;
            return;
        }

        std::cout << name_ << " бросил игрушку " << toy_->getNmae() << " на пол." << std::endl;
        toy_ = nullptr; // Сбрасываем указатель
    }
};

// контроль ввода
int getValidatedChoice() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите корректное число: ";
        } else {
            return choice;
        }
    }
}

int main() {
    // Создаем двух собак для демонстрации взаимодействия
    Dog dog1("Шарик");
    Dog dog2("Бобик");

    std::shared_ptr<Toy> masterToy = nullptr;
    std::string toyName;

    while (true) {
        std::cout << "\n=== ТЕКСТОВЫЙ ИНТЕРФЕЙС ИГРЫ С СОБАКАМИ ===" << std::endl;
        std::cout << "1. Создать новую игрушку" << std::endl;
        std::cout << "2. Шарик, взять игрушку (getToy)" << std::endl;
        std::cout << "3. Шарик, бросить игрушку (dropToy)" << std::endl;
        std::cout << "4. Бобик, взять игрушку (getToy)" << std::endl;
        std::cout << "5. Бобик, бросить игрушку (dropToy)" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;
        std::cout << "Выберите действие: ";

        int choice = getValidatedChoice();

        if (choice == 0) {
            std::cout << "Выход из программы. Уничтожение оставшихся объектов:" << std::endl;
            break;
        }

        switch (choice) {
            case 1:
                std::cout << "Введите название игрушки: ";
                std::cin >> toyName; 
                
                masterToy = std::make_shared<Toy>(toyName);
                std::cout << "Игрушка " << toyName << " успешно создана на полу." << std::endl;
                break;
            case 2:
                dog1.getToy(masterToy);
                break;
            case 3:
                dog1.dropToy();
                break;
            case 4:
                dog2.getToy(masterToy);
                break;
            case 5:
                dog2.dropToy();
                break;
            default:
                std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
                break;
        }
    }

    return 0;
}
