#include <iostream>

int main() {
    // Настройка русского языка
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int bacteria = 0;
    int antibioticDrops = 0;

    std::cout << "Введите количество бактерий: ";
    std::cin >> bacteria;
    std::cout << "Введите количество антибиотика: ";
    std::cin >> antibioticDrops;

    // Проверка ввода
    if (bacteria <= 0 || antibioticDrops <= 0) {
        std::cout << "Ошибка! Количество бактерий и антибиотика должно быть больше нуля.\n";
        return 1;
    }

    int hour = 1;
    int dropPower = 10; // В первый час одна капля убивает 10 бактерий

    // Цикл работает, пока есть бактерии и антибиотик еще действует
    while (bacteria > 0 && dropPower > 0) {
        // Сначала бактерии удваиваются
        bacteria *= 2;

        // Затем действует антибиотик
        int killedBacteria = antibioticDrops * dropPower;
        bacteria -= killedBacteria;

        // Количество бактерий не может быть отрицательным
        if (bacteria < 0) {
            bacteria = 0;
        }

        std::cout << "После " << hour << " часа бактерий осталось " << bacteria << "\n";

        // Если все бактерии погибли, выходим из цикла
        if (bacteria == 0) {
            std::cout << "Все бактерии уничтожены!\n";
            break;
        }

        // Переходим к следующему часу, сила антибиотика падает
        hour++;
        dropPower--;
    }

    if (bacteria > 0) {
        std::cout << "Антибиотик перестал действовать, бактерии выжили.\n";
    }

    return 0;
}
