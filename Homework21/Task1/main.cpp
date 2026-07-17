#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Класс аудиозаписи 
class Track {
public:
    std::string title;
    std::tm creationDate;
    int durationSeconds = 0;
};

// Класс аудиоплеера 
class Player {
private:
    std::vector<Track> playlist;
    int currentTrackIndex = -1; // -1 означает, что трек не выбран
    bool isPlaying = false;
    bool isPaused = false;

    // Вспомогательный метод для красивого вывода информации о треке
    void displayTrackInfo(const Track& track) const {
        std::cout << "--- Название: " << track.title << "\n";
        // Выводим дату в привычном формате ДД.ММ.ГГГГ
        std::cout << "    Дата создания: " 
                  << (track.creationDate.tm_mday < 10 ? "0" : "") << track.creationDate.tm_mday << "."
                  << (track.creationDate.tm_mon + 1 < 10 ? "0" : "") << (track.creationDate.tm_mon + 1) << "."
                  << (track.creationDate.tm_year + 1900) << "\n";
        std::cout << "    Продолжительность: " << track.durationSeconds / 60 << " мин. " 
                  << track.durationSeconds % 60 << " сек.\n";
    }

public:
    // Метод добавления треков в плеер при инициализации
    void addTrack(const Track& track) {
        playlist.push_back(track);
    }

    // Команда play 
    void play() {
        if (isPlaying && !isPaused) {
            std::cout << "Запись уже воспроизводится.\n";
            return;
        }

        if (isPaused) {
            isPaused = false;
            std::cout << "Воспроизведение возобновлено.\n";
            displayTrackInfo(playlist[currentTrackIndex]);
            return;
        }

        std::string searchTitle;
        std::cout << "Введите название записи для воспроизведения: ";
        std::cin >> searchTitle;

        int foundIndex = -1;
        for (size_t i = 0; i < playlist.size(); ++i) {
            if (playlist[i].title == searchTitle) {
                foundIndex = static_cast<int>(i);
                break;
            }
        }

        if (foundIndex != -1) {
            currentTrackIndex = foundIndex;
            isPlaying = true;
            isPaused = false;
            std::cout << "Начало воспроизведения:\n";
            displayTrackInfo(playlist[currentTrackIndex]);
        } else {
            std::cout << "Ошибка: Запись с таким названием не найдена.\n";
        }
    }

    // Команда pause 
    void pause() {
        if (!isPlaying || isPaused) {
            return; // Если не воспроизводится вовсе или уже на паузе — ничего не происходит
        }
        isPaused = true;
        std::cout << "Воспроизведение поставлено на паузу.\n";
    }

    // Команда next  
    void next() {
        if (playlist.empty()) {
            std::cout << "Плейлист пуст.\n";
            return;
        }
        
        // Выбираем случайный трек
        currentTrackIndex = std::rand() % playlist.size();
        isPlaying = true;
        isPaused = false;
        std::cout << "Переход к следующей случайной записи:\n";
        displayTrackInfo(playlist[currentTrackIndex]);
    }

    // Команда stop 
    void stop() {
        if (!isPlaying) {
            return; // Два раза остановить невозможно
        }
        isPlaying = false;
        isPaused = false;
        std::cout << "Воспроизведение трека \"" << playlist[currentTrackIndex].title << "\" остановлено.\n";
        currentTrackIndex = -1;
    }
};

int main() {
    std::srand(std::time(nullptr));
    Player myPlayer;

    // Наполняем плеер тестовыми треками для симуляции
    Track t1{"SongA", {0, 0, 0, 15, 6, 126}, 185}; // 15.07.2026, 3 мин 5 сек
    Track t2{"SongB", {0, 0, 0, 20, 11, 125}, 240}; // 20.12.2025, 4 мин 0 сек
    Track t3{"SongC", {0, 0, 0, 1, 0, 124}, 122}; // 01.01.2024, 2 мин 2 сек

    myPlayer.addTrack(t1);
    myPlayer.addTrack(t2);
    myPlayer.addTrack(t3);

    std::cout << "=== Имитация работы аудиоплеера ===\n";
    std::cout << "Доступные треки в системе: SongA, SongB, SongC\n";
    std::cout << "Доступные команды: play, pause, next, stop, exit\n\n";

    std::string command;
    while (true) {
        std::cout << "\nВведите команду: ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Работа плеера завершена.\n";
            break;
        }
        else if (command == "play") {
            myPlayer.play();
        }
        else if (command == "pause") {
            myPlayer.pause();
        }
        else if (command == "next") {
            myPlayer.next();
        }
        else if (command == "stop") {
            myPlayer.stop();
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова.\n";
        }
    }

    return 0;
}
