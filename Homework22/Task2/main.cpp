#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Базовый класс для всех сотрудников компании
class Employee {
protected:
    std::string name;
public:
    Employee(std::string name) {
        this->name = name;
    }
    std::string getName() const {
        return this->name;
    }
    virtual ~Employee() {}
};

// Класс обычного рабочего
class Worker : public Employee {
private:
    bool isBusy = false;
    char taskType = ' ';
public:
    Worker(std::string name) : Employee(name) {}

    bool getIsBusy() const {
        return this->isBusy;
    }

    void assignTask(char type) {
        this->isBusy = true;
        this->taskType = type;
        std::cout << "  [Рабочий] " << getName() << " взял задачу типа " << this->taskType << "\n";
    }
};

// Класс менеджера среднего звена
class Manager : public Employee {
private:
    int teamId;
    std::vector<Worker*> team;
public:
    Manager(std::string name, int id) : Employee(name) {
        this->teamId = id;
    }

    ~Manager() {
        for (auto* worker : team) delete worker;
    }

    void addWorker(Worker* worker) {
        this->team.push_back(worker);
    }

    int getTeamSize() const {
        return this->team.size();
    }

    // Возвращает количество свободных работников в команде
    int getFreeWorkersCount() const {
        int count = 0;
        for (const auto* w : team) {
            if (!w->getIsBusy()) count++;
        }
        return count;
    }

    // Обработка указания директора 
    void processDirectorOrder(int orderNumber) {
        std::cout << "[Менеджер] " << getName() << " (Команда №" << this->teamId 
                  << ") принял указание директора №" << orderNumber << "\n";

        // Инициализируем генератор случайных чисел: ID команды + указание директора
        int hash = orderNumber + this->teamId;
        std::srand(hash);

        // Вычисляем общее количество задач  
        int maxTasks = this->team.size();
        int tasksCount = (std::rand() % maxTasks) + 1;
        std::cout << "  -> Команде выделено " << tasksCount << " случайных задач.\n";

        // Распределяем задачи среди незанятых рабочих
        for (int i = 0; i < tasksCount; ++i) {
            // Ищем первого свободного рабочего
            Worker* freeWorker = nullptr;
            for (auto* w : team) {
                if (!w->getIsBusy()) {
                    freeWorker = w;
                    break;
                }
            }

            // Если свободных рабочих больше нет, прерываем распределение
            if (freeWorker == nullptr) {
                break;
            }

            // Случайно выбираем тип задачи: A, B или C 
            int taskChoice = std::rand() % 3;
            char type = (taskChoice == 0) ? 'A' : (taskChoice == 1) ? 'B' : 'C';

            freeWorker->assignTask(type);
        }
    }
};

// Класс главы компании
class Director : public Employee {
private:
    std::vector<Manager*> managers;
public:
    Director(std::string name) : Employee(name) {}

    ~Director() {
        for (auto* manager : managers) delete manager;
    }

    void addManager(Manager* manager) {
        this->managers.push_back(manager);
    }

    // Проверяем, заняты ли абсолютно все сотрудники в компании 
    bool isCompanyFullyOccupied() const {
        for (const auto* m : managers) {
            if (m->getFreeWorkersCount() > 0) {
                return false;
            }
        }
        return true;
    }

    // Раздать указание всем менеджерам
    void issueOrder(int orderNumber) {
        std::cout << "\n[Директор] " << getName() << " выдает указание №" << orderNumber << "...\n";
        for (auto* m : managers) {
            m->processDirectorOrder(orderNumber);
        }
    }
};

int main() {
    std::cout << "=== Симуляция работы компании ===\n";

    int numTeams, numWorkersPerTeam;
    std::cout << "Введите количество команд: ";
    std::cin >> numTeams;
    std::cout << "Введите количество работников в каждой команде: ";
    std::cin >> numWorkersPerTeam;

    Director* director = new Director("GigaBoss");

    // Формируем структуру компании
    for (int t = 0; t < numTeams; ++t) {
        Manager* manager = new Manager("Manager_" + std::to_string(t + 1), t + 1);
        for (int w = 0; w < numWorkersPerTeam; ++w) {
            Worker* worker = new Worker("Worker_" + std::to_string(t + 1) + "_" + std::to_string(w + 1));
            manager->addWorker(worker);
        }
        director->addManager(manager);
    }

    std::cout << "\nКомпания успешно сформирована и готова к работе!\n";

    // Цикл указаний руководителя
    while (true) {
        if (director->isCompanyFullyOccupied()) {
            std::cout << "\n🎉 Все работники компании заняты задачами! Симуляция завершена.\n";
            break;
        }

        int orderNumber;
        std::cout << "\nВведите целочисленное указание руководителя: ";
        std::cin >> orderNumber;

        director->issueOrder(orderNumber);
    }

    delete director; // Очищаем всю иерархию выделенной памяти
    return 0;
}
