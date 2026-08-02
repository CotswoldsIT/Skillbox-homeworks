#include <iostream>
#include <vector>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Перечисление типов комнат 
enum RoomType {
    LIVING,
    CHILDREN,
    KITCHEN,
    BATHROOM,
    BEDROOM
};

// Перечисление типов построек 
enum BuildingType {
    HOUSE,
    GARAGE,
    BARN,
    BATHHOUSE
};

// Структура комнаты
struct Room {
    RoomType type;
    double area = 0.0;
};

// Структура этажа
struct Floor {
    double ceilingHeight = 0.0;
    std::vector<Room> rooms;
};

// Структура здания
struct Building {
    BuildingType type;
    double area = 0.0;
    bool hasOven = false; // Актуально для дома и бани
    std::vector<Floor> floors; // Актуально только для дома
};

// Структура участка
struct Plot {
    int id = 0;
    double totalArea = 0.0;
    std::vector<Building> buildings;
};

// Функция для текстового перевода типа здания
std::string get_building_name(BuildingType type) {
    if (type == HOUSE) return "Жилой дом";
    if (type == GARAGE) return "Гараж";
    if (type == BARN) return "Сарай";
    return "Баня";
}

int main() {
    int totalPlots = 0;
    std::cout << "=== Система моделирования данных посёлка ===\n";
    std::cout << "Введите общее количество участков в посёлке: ";
    std::cin >> totalPlots;

    std::vector<Plot> village;
    double globalTotalArea = 0.0;
    double globalBuildingsArea = 0.0;

    // Пошаговое заполнение структур 
    for (int i = 0; i < totalPlots; ++i) {
        Plot plot;
        std::cout << "\n--- Заполнение данных для участка №" << (i + 1) << " ---\n";
        plot.id = i + 1;
        
        std::cout << "Введите общую площадь участка (кв. м): ";
        std::cin >> plot.totalArea;
        globalTotalArea += plot.totalArea;

        int buildingsCount = 0;
        std::cout << "Сколько построек на этом участке? ";
        std::cin >> buildingsCount;

        for (int b = 0; b < buildingsCount; ++b) {
            Building building;
            int typeChoice = 0;
            std::cout << "  Выберите тип постройки №" << (b + 1) << " (0 - Дом, 1 - Гараж, 2 - Сарай, 3 - Баня): ";
            std::cin >> typeChoice;
            building.type = static_cast<BuildingType>(typeChoice);

            std::cout << "  Введите площадь, занимаемую постройкой на земле (кв. м): ";
            std::cin >> building.area;
            globalBuildingsArea += building.area;

            if (building.type == HOUSE || building.type == BATHHOUSE) {
                char ovenChoice;
                std::cout << "  Есть ли в этой постройке печь с трубой? (y/n): ";
                std::cin >> ovenChoice;
                building.hasOven = (ovenChoice == 'y' || ovenChoice == 'Y');
            }

            // Детализация этажей и комнат жилого дома
            if (building.type == HOUSE) {
                int floorsCount = 0;
                std::cout << "  Сколько этажей в доме (от 1 до 3)? ";
                std::cin >> floorsCount;
                if (floorsCount < 1) floorsCount = 1;
                if (floorsCount > 3) floorsCount = 3;

                for (int f = 0; f < floorsCount; ++f) {
                    Floor floor;
                    std::cout << "    [Этаж " << (f + 1) << "] Введите высоту потолка (м): ";
                    std::cin >> floor.ceilingHeight;

                    int roomsCount = 0;
                    std::cout << "    [Этаж " << (f + 1) << "] Сколько комнат на этаже (от 2 до 4)? ";
                    std::cin >> roomsCount;
                    if (roomsCount < 2) roomsCount = 2;
                    if (roomsCount > 4) roomsCount = 4;

                    for (int r = 0; r < roomsCount; ++r) {
                        Room room;
                        int roomTypeChoice = 0;
                        std::cout << "      Комната №" << (r + 1) << " (0-Гостиная, 1-Детская, 2-Кухня, 3-Ванная, 4-Спальня): ";
                        std::cin >> roomTypeChoice;
                        room.type = static_cast<RoomType>(roomTypeChoice);

                        std::cout << "      Введите площадь этой комнаты (кв. м): ";
                        std::cin >> room.area;
                        floor.rooms.push_back(room);
                    }
                    building.floors.push_back(floor);
                }
            }
            plot.buildings.push_back(building);
        }
        village.push_back(plot);
    }

    // Расчет суммарного параметра 
    std::cout << "\n=== ИТОГОВЫЙ АНАЛИЗ ПОСЁЛКА ===\n";
    std::cout << "Общая площадь земли посёлка: " << globalTotalArea << " кв. м.\n";
    std::cout << "Суммарная площадь под постройками: " << globalBuildingsArea << " кв. m.\n";
    if (globalTotalArea > 0) {
        double percentage = (globalBuildingsArea / globalTotalArea) * 100.0;
        std::cout << "Процент земли, занимаемый постройками: " << percentage << " %\n";
    }

    return 0;
}
