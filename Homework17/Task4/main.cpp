#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

const int MAP_SIZE = 20;

struct Position {
    int x = 0;
    int y = 0;
};

struct Character {
    std::string name;
    int health = 0;
    int armor = 0;
    int damage = 0;
    Position position;
    bool isPlayer = false;
    bool isDead = false;
};

// Функция отрисовки карты
void draw_map(const std::vector<Character>& characters) {
    char map[MAP_SIZE][MAP_SIZE];
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            map[y][x] = '.';
        }
    }

    for (const auto& c : characters) {
        if (!c.isDead) {
            map[c.position.y][c.position.x] = c.isPlayer ? 'P' : 'E';
        }
    }

    std::cout << "\n--- ИГРОВОЕ ПОЛЕ ---\n";
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            std::cout << map[y][x] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n";
}

// Поиск персонажа в клетке
int get_character_at(int x, int y, const std::vector<Character>& characters) {
    for (size_t i = 0; i < characters.size(); ++i) {
        if (!characters[i].isDead && characters[i].position.x == x && characters[i].position.y == y) {
            return i;
        }
    }
    return -1;
}

// Расчет боя по формуле
void take_damage(Character& defender, int damage) {
    defender.armor -= damage;
    if (defender.armor < 0) {
        defender.health += defender.armor;
        defender.armor = 0;
    }
    if (defender.health <= 0) {
        defender.health = 0;
        defender.isDead = true;
        std::cout << defender.name << " погибает!\n";
    }
}

// Сохранение игры
void save_game(const std::vector<Character>& characters) {
    std::ofstream file("save.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Ошибка: Не удалось создать файл сохранения!\n";
        return;
    }
    
    size_t size = characters.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(size));

    for (const auto& c : characters) {
        size_t name_len = c.name.size();
        file.write(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        file.write(c.name.data(), name_len);

        file.write(reinterpret_cast<const char*>(&c.health), sizeof(c.health));
        file.write(reinterpret_cast<const char*>(&c.armor), sizeof(c.armor));
        file.write(reinterpret_cast<const char*>(&c.damage), sizeof(c.damage));
        file.write(reinterpret_cast<const char*>(&c.position), sizeof(c.position));
        file.write(reinterpret_cast<const char*>(&c.isPlayer), sizeof(c.isPlayer));
        file.write(reinterpret_cast<const char*>(&c.isDead), sizeof(c.isDead));
    }
    file.close();
    std::cout << "Игра успешно сохранена в файл save.bin!\n";
}

// Загрузка игры
bool load_game(std::vector<Character>& characters) {
    std::ifstream file("save.bin", std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Ошибка: Файл сохранения save.bin не найден на диске!\n";
        return false;
    }

    characters.clear();
    size_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    for (size_t i = 0; i < size; ++i) {
        Character c;
        size_t name_len;
        file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        c.name.resize(name_len);
        file.read(&c.name[0], name_len); //  чтение бинарной строки

        file.read(reinterpret_cast<char*>(&c.health), sizeof(c.health));
        file.read(reinterpret_cast<char*>(&c.armor), sizeof(c.armor));
        file.read(reinterpret_cast<char*>(&c.damage), sizeof(c.damage));
        file.read(reinterpret_cast<char*>(&c.position), sizeof(c.position));
        file.read(reinterpret_cast<char*>(&c.isPlayer), sizeof(c.isPlayer));
        file.read(reinterpret_cast<char*>(&c.isDead), sizeof(c.isDead));
        characters.push_back(c);
    }
    file.close();
    std::cout << "Игра успешно загружена из файла save.bin!\n";
    return true;
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<Character> characters;

    Character player;
    player.isPlayer = true;
    std::cout << "=== СОЗДАНИЕ ВАШЕГО ПЕРСОНАЖА ===\n";
    std::cout << "Введите имя героя: ";
    std::cin >> player.name;
    std::cout << "Введите очки здоровья: ";
    std::cin >> player.health;
    std::cout << "Введите очки брони: ";
    std::cin >> player.armor;
    player.damage = 25; 
    player.position = {std::rand() % MAP_SIZE, std::rand() % MAP_SIZE};
    characters.push_back(player);

    for (int i = 0; i < 5; ++i) {
        Character enemy;
        enemy.name = "Enemy #" + std::to_string(i + 1);
        enemy.health = 50 + std::rand() % 101;
        enemy.armor = std::rand() % 51;
        enemy.damage = 15 + std::rand() % 16;
        
        while (true) {
            Position pos = {std::rand() % MAP_SIZE, std::rand() % MAP_SIZE};
            if (get_character_at(pos.x, pos.y, characters) == -1) {
                enemy.position = pos;
                break;
            }
        }
        characters.push_back(enemy);
    }

    while (true) {
        if (characters[0].isDead) {
            std::cout << "\nВы погибли. ПОРАЖЕНИЕ!\n";
            break;
        }
        bool allEnemiesDead = true;
        for (size_t i = 1; i < characters.size(); ++i) {
            if (!characters[i].isDead) allEnemiesDead = false;
        }
        if (allEnemiesDead) {
            std::cout << "\nВсе противники повержены. ПОБЕДА!\n";
            break;
        }

        draw_map(characters);

        std::string command;
        std::cout << "Ваш ход (W/A/S/D — движение, save — сохранить, load — загрузить): ";
        std::cin >> command;

        if (command == "save") {
            save_game(characters);
            continue;
        } else if (command == "load") {
            load_game(characters);
            continue;
        }

        int dx = 0, dy = 0;
        if (command == "A" || command == "a") dx = -1;
        else if (command == "D" || command == "d") dx = 1;
        else if (command == "W" || command == "w") dy = -1;
        else if (command == "S" || command == "s") dy = 1;
        else {
            std::cout << "Неизвестная команда!\n";
            continue;
        }

        // Логика хода игрока
        int newX = characters[0].position.x + dx;
        int newY = characters[0].position.y + dy;

        if (newX >= 0 && newX < MAP_SIZE && newY >= 0 && newY < MAP_SIZE) {
            int targetIdx = get_character_at(newX, newY, characters);
            if (targetIdx == -1) {
                characters[0].position.x = newX;
                characters[0].position.y = newY;
            } else if (!characters[targetIdx].isPlayer) {
                std::cout << "Вы атакуете " << characters[targetIdx].name << " на " << characters[0].damage << " урона!\n";
                take_damage(characters[targetIdx], characters[0].damage);
            }
        }

        // Логика хода врагов
        for (size_t i = 1; i < characters.size(); ++i) {
            if (characters[i].isDead) continue;

            int edx = 0, edy = 0;
            int dir = std::rand() % 4;
            if (dir == 0) edx = -1;
            else if (dir == 1) edx = 1;
            else if (dir == 2) edy = -1;
            else edy = 1;

            int enewX = characters[i].position.x + edx;
            int enewY = characters[i].position.y + edy;

            if (enewX >= 0 && enewX < MAP_SIZE && enewY >= 0 && enewY < MAP_SIZE) {
                int targetIdx = get_character_at(enewX, enewY, characters);
                if (targetIdx == -1) {
                    characters[i].position.x = enewX;
                    characters[i].position.y = enewY;
                } else if (characters[targetIdx].isPlayer) {
                    std::cout << characters[i].name << " атакует вас на " << characters[i].damage << " урона!\n";
                    take_damage(characters[targetIdx], characters[i].damage);
                }
            }
        }
    }

    return 0;
}
