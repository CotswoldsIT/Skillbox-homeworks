#include <iostream>
#include <string>
#include <limits>
#include <clocale>

// Настройка русского языка в консоли
const bool init_locale = []() { std::setlocale(LC_ALL, "ru_RU.UTF-8"); return true; }();

class Toy {
public:
    Toy(const std::string& name) {
        name_ = name;
    }
    std::string getNmae() { //  метод из ТЗ 
        return name_;
    }
    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped" << std::endl;
    }
private:
    std::string name_;
};

class shared_ptr_toy {
private:
    Toy* ptr_ = nullptr;       // Указатель на управляемый объект Toy
    int* ref_count_ = nullptr; // Указатель на общий счетчик ссылок в куче

    // Вспомогательный приватный метод для освобождения ресурсов
    void release() {
        if (ref_count_ != nullptr) {
            (*ref_count_)--;
            if (*ref_count_ == 0) {
                delete ptr_;
                delete ref_count_;
            }
        }
        ptr_ = nullptr;
        ref_count_ = nullptr;
    }

public:
    // 1. Конструктор по умолчанию
    shared_ptr_toy() : ptr_(nullptr), ref_count_(nullptr) {}

    // 2. Конструктор с одним параметром («Имя игрушки»)
    shared_ptr_toy(const std::string& name) {
        ptr_ = new Toy(name);
        ref_count_ = new int(1);
    }

    // 3. Конструктор копирования
    shared_ptr_toy(const shared_ptr_toy& other) {
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if (ref_count_ != nullptr) {
            (*ref_count_)++;
        }
    }

    // 4. Перегрузка оператора присваивания
    shared_ptr_toy& operator=(const shared_ptr_toy& other) {
        if (this->ptr_ == other.ptr_) {
            return *this; // Текущий объект уже содержит ссылку на нужный Toy
        }

        release(); // Освобождаем текущую ссылку на Toy

        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if (ref_count_ != nullptr) {
            (*ref_count_)++;
        }
        return *this;
    }

    // 5. Деструктор
    ~shared_ptr_toy() {
        release();
    }

    // Метод reset()
    void reset() {
        release();
    }

    // Метод get()
    Toy* get() const {
        return ptr_;
    }

    // Метод use_count()
    int use_count() const {
        return (ref_count_ != nullptr) ? *ref_count_ : 0;
    }

    // Вспомогательный метод получения имени игрушки
    std::string getToyName() const {
        return (ptr_ != nullptr) ? ptr_->getNmae() : "Nothing";
    }
};

// Сервисная функция make_shared_toy
shared_ptr_toy make_shared_toy(const std::string& name) {
    return shared_ptr_toy(name);
}

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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

// Отдельная функция для демонстрации теста из ТЗ
void runStandardTest() {
    std::cout << "\n--- ЗАПУСК ЭТАЛОННОГО ТЕСТА С ПЛАТФОРМЫ SKILLBOX ---" << std::endl;
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03("duck");
    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
              << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
              << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
}

int main() {
    // Интерактивный интерфейс для выполнения критериев оценки работы
    shared_ptr_toy user_toy1;
    shared_ptr_toy user_toy2;
    std::string inputName;

    while (true) {
        std::cout << "\n=== ТЕКСТОВЫЙ ИНТЕРФЕЙС УПРАВЛЕНИЯ УКАЗАТЕЛЯМИ ===" << std::endl;
        std::cout << "Текущий статус указателей:" << std::endl;
        std::cout << "Указатель 1: " << user_toy1.getToyName() << " (ссылок: " << user_toy1.use_count() << ")" << std::endl;
        std::cout << "Указатель 2: " << user_toy2.getToyName() << " (ссылок: " << user_toy2.use_count() << ")" << std::endl;
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "1. Инициализировать Указатель 1 через make_shared_toy" << std::endl;
        std::cout << "2. Скопировать Указатель 1 в Указатель 2 (оператор =)" << std::endl;
        std::cout << "3. Сбросить Указатель 1 (reset)" << std::endl;
        std::cout << "4. Сбросить Указатель 2 (reset)" << std::endl;
        std::cout << "5. ЗАПУСТИТЬ ЭТАЛОННЫЙ ТЕСТ ИЗ ЗАДАНИЯ" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;
        std::cout << "Выберите действие: ";

        int choice = getValidatedChoice();

        if (choice == 0) {
            std::cout << "Выход из программы. Очистка оставшейся памяти:" << std::endl;
            break;
        }

        switch (choice) {
            case 1:
                std::cout << "Введите название игрушки для Указателя 1: ";
                std::cin >> inputName;
                user_toy1 = make_shared_toy(inputName);
                break;
            case 2:
                user_toy2 = user_toy1;
                std::cout << "Указатель 1 успешно скопирован в Указатель 2." << std::endl;
                break;
            case 3:
                user_toy1.reset();
                std::cout << "Указатель 1 сброшен." << std::endl;
                break;
            case 4:
                user_toy2.reset();
                std::cout << "Указатель 2 сброшен." << std::endl;
                break;
            case 5:
                runStandardTest();
                break;
            default:
                std::cout << "Неверный пункт меню. Попробуйте снова." << std::endl;
                break;
        }
    }

    return 0;
}
