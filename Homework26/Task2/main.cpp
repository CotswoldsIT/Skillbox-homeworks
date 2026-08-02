#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

struct SearchResult {
    std::string movieTitle;
    std::string characterName;
};

int main() {
    auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    
    std::ifstream file("movies.json");
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл movies.json" << std::endl;
        return 1;
    }

    std::string actorToSearch;
    std::cout << "Введите имя актера для поиска (например, Леонардо): ";
    std::getline(std::cin, actorToSearch);

    std::string line;
    std::string currentMovie = "";
    std::vector<SearchResult> results;

    while (std::getline(file, line)) {
        // Запоминаем название текущего фильма
        if (line.find("\"title\":") != std::string::npos) {
            size_t start = line.find("\"title\":") + 8;
            start = line.find("\"", start) + 1;
            size_t end = line.find("\"", start);
            currentMovie = line.substr(start, end - start);
        }
        
        // Если в строке есть нужный актер
        if (line.find("\"actor\":") != std::string::npos && line.find(actorToSearch) != std::string::npos) {
            // Ищем роль в этой же строке
            size_t charPos = line.find("\"character\":");
            if (charPos != std::string::npos) {
                size_t start = line.find("\"", charPos + 12) + 1;
                size_t end = line.find("\"", start);
                std::string character = line.substr(start, end - start);
                results.push_back({currentMovie, character});
            }
        }
    }

    file.close();

    if (results.empty()) {
        std::cout << "Актер \"" << actorToSearch << "\" не найден в базе данных." << std::endl;
    } else {
        std::cout << "\nРезультаты поиска для актера: " << actorToSearch << "\n";
        for (const auto& res : results) {
            std::cout << "- Фильм: \"\x1b[32m" << res.movieTitle << "\x1b[0m\", Роль: \x1b[33m" << res.characterName << "\x1b[0m" << std::endl;
        }
    }

    return 0;
}
