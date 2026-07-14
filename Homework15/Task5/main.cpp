#include <iostream>
#include <fstream>
#include <string>

// Настройка русского языка
auto locale_init = std::setlocale(LC_ALL, "ru_RU.UTF-8");

// Автоматическая генерация файлов с вопросами и ответами
void generate_questions_and_answers() {
    for (int i = 0; i < 13; ++i) {
        std::string q_path = "question_" + std::to_string(i + 1) + ".txt";
        std::string a_path = "answer_" + std::to_string(i + 1) + ".txt";

        std::ifstream check_q(q_path);
        if (!check_q.is_open()) {
            std::ofstream out_q(q_path);
            out_q << "Вопрос для сектора " << (i + 1) << ": Назовите столицу Ирландии (на английском языке).";
            out_q.close();
            
            std::ofstream out_a(a_path);
            out_a << "Dublin"; // Ответ на латинице для совместимости кодировок,иначе на русском выдает неверный ответ
            out_a.close();
        } else {
            check_q.close();
        }
    }
}

int main() {
    generate_questions_and_answers();

    bool played_sectors[13] = {false}; // Массив сыгранных секторов
    int current_sector = 0;            // Стрелка изначально на первом секторе
    int player_score = 0;
    int viewers_score = 0;

    std::cout << "=== ИГРА «ЧТО? ГДЕ? КОГДА?» ===\n";
    std::cout << "Правила: Игра идёт до 6 очков. На барабане 13 секторов. Ответ вводится одним словом.\n";
    std::cout << "Подсказка для теста: правильный ответ — Dublin\n";

    while (player_score < 6 && viewers_score < 6) {
        std::cout << "\nСчёт: Знатоки " << player_score << " — " << viewers_score << " Телезрители\n";
        std::cout << "Стрелка находится на секторе " << (current_sector + 1) << "\n";
        
        int offset;
        std::cout << "Вращайте волчок! Введите смещение (целое число): ";
        std::cin >> offset;

        current_sector = (current_sector + offset) % 13;
        if (current_sector < 0) {
            current_sector += 13;
        }

        while (played_sectors[current_sector]) {
            current_sector = (current_sector + 1) % 13;
        }

        played_sectors[current_sector] = true;
        std::cout << "\n=== ИГРАЕТ СЕКТОР " << (current_sector + 1) << " ===\n";

        std::ifstream question_file("question_" + std::to_string(current_sector + 1) + ".txt");
        std::string question_text;
        if (question_file.is_open()) {
            std::getline(question_file, question_text);
            question_file.close();
            std::cout << "Вопрос: " << question_text << "\n";
        } else {
            std::cout << "Ошибка: Не удалось открыть файл с вопросом!\n";
            return 1;
        }

        std::string player_answer;
        std::cout << "Ваш ответ (одно слово): ";
        std::cin >> player_answer;

        std::ifstream answer_file("answer_" + std::to_string(current_sector + 1) + ".txt");
        std::string correct_answer;
        if (answer_file.is_open()) {
            answer_file >> correct_answer;
            answer_file.close();
        } else {
            std::cout << "Ошибка: Не удалось открыть... файл с ответом!\n";
            return 1;
        }

        if (player_answer == correct_answer) {
            std::cout << "Правильно! Знатоки получают 1 балл.\n";
            player_score++;
        } else {
            std::cout << "Неверно! Правильный ответ: " << correct_answer << ". Балл уходит телезрителям.\n";
            viewers_score++;
        }
    }

    std::cout << "\n=== ИГРА ЗАВЕРШЕНА ===\n";
    std::cout << "Финальный счёт: Знатоки " << player_score << " — " << viewers_score << " Телезрители\n";
    if (player_score >= 6) {
        std::cout << "Поздравляем! Победили Знатоки!\n";
    } else {
        std::cout << "Увы! Победили Телезрители!\n";
    }

    return 0;
}
