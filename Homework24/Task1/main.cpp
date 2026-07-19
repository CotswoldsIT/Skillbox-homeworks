#include <iostream>
#include <string>
#include <vector>
#include <clocale>   
#include <windows.h> // Нужен для точной настройки кодировки

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// абстрактный класс «Талант»
class Talent {
public:
    virtual ~Talent() = default; // Виртуальный деструктор для безопасного удаления наследников
    virtual void show() = 0;     //  функция делает класс абстрактным
};

// Класс-способность: Умение плавать
class Swimming : public Talent {
public:
    void show() override {
        std::cout << "            It can \"Swim\"\n";
    }
};

// Класс-способность: Умение танцевать
class Dancing : public Talent {
public:
    void show() override {
        std::cout << "            It can \"Dance\"\n";
    }
};

// Класс-способность: Умение считать
class Counting : public Talent {
public:
    void show() override {
        std::cout << "            It can \"Count\"\n";
    }
};

// Класс Собака 
class Dog {
private:
    std::string name;
    std::vector<Talent*> talents; // Вектор указателей для хранения способностей

public:
    // Конструктор
    Dog(std::string in_name) : name(in_name) {}

    // Деструктор для очистки динамической памяти
    ~Dog() {
        for (auto talent : talents) {
            delete talent;
        }
        talents.clear();
    }

    // Метод для добавления таланта собаке
    void add_talent(Talent* new_talent) {
        if (new_talent != nullptr) {
            talents.push_back(new_talent);
        }
    }

    // Метод для показа всех способностей собаки
    void show_talents() {
        std::cout << "This is " << name << " and it has some talents:\n";
        if (talents.empty()) {
            std::cout << "            It has no special talents yet.\n";
            return;
        }
        // Последовательно вызываем каждое умение
        for (auto talent : talents) {
            talent->show();
        }
    }
};

int main() {
    // Включаем поддержку UTF-8 в консоли Windows
    SetConsoleCP(65001);       
    SetConsoleOutputCP(65001); 

    std::cout << "=== Тестирование класса Суперпёс ===\n\n";

    // Создаём собаку с именем Steve
    Dog dog1("Steve");

    // Добавляем ей умение танцевать и плавать 
    dog1.add_talent(new Dancing());
    dog1.add_talent(new Swimming());

    // Запрос умений
    dog1.show_talents();

    std::cout << "\n====================================\n";
    return 0;
}
