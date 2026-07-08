#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    // Начальные параметры в сантиметрах
    int beginHeight = 100;   // 1 метр = 100 см
    int dailyGrowth = 50;    // Рост за день
    int nightFade = 20;      // Съедают за ночь

    std::cout << "--- Расчёт роста бамбука ---\n";
    std::cout << "Начальная высота бамбука (см): " << beginHeight << "\n";
    std::cout << "Ежедневный рост бамбука (см): " << dailyGrowth << "\n";
    std::cout << "Сколько съедают гусеницы за ночь (см): " << nightFade << "\n";

    // Формула расчета значений к середине третьего дня:
    // Прошло 2 полных суток (2 дня и 2 ночи) + половина третьего дня (только рост / 2)
    int finalHeight = beginHeight + (dailyGrowth - nightFade) * 2 + dailyGrowth / 2;

    std::cout << "------------------------------------\n";
    std::cout << "В середине третьего дня высота бамбука составит: " << finalHeight << " см.\n";

    return 0;
}
