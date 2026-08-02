#include <iostream>
#include <string>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    std::string secret, guess;
    std::cout << "Введите задуманное число: ";
    std::cin >> secret;
    std::cout << "Введите второе число: ";
    std::cin >> guess;

    // Контроль ввода: числа должны быть строго четырёхзначными
    if (secret.length() != 4 || guess.length() != 4) {
        std::cout << "Ошибка! Числа должны состоять ровно из 4 цифр.\n";
        return 1;
    }

    int bulls = 0;
    int cows = 0;

    // Массивы флагов, чтобы не считать одну и ту же цифру дважды
    bool secretUsed[4] = {false, false, false, false};
    bool guessUsed[4] = {false, false, false, false};

    // Шаг 1: Считаем быков (совпадение и по цифре, и по позиции)
    for (int i = 0; i < 4; i++) {
        if (guess[i] == secret[i]) {
            bulls++;
            secretUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    // Шаг 2: Считаем коров (совпадение только по цифре на других позициях)
    for (int i = 0; i < 4; i++) {
        if (guessUsed[i]) continue; // Если цифра уже стала быком, пропускаем её

        for (int j = 0; j < 4; j++) {
            if (!secretUsed[j] && guess[i] == secret[j]) {
                cows++;
                secretUsed[j] = true; // Помечаем, что эта цифра секрета задействована
                break; // Переходим к следующей цифре догадки
            }
        }
    }

    std::cout << "Быков: " << bulls << ", коров: " << cows << "\n";

    return 0;
}
