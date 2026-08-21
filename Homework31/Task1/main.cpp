#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1. главное окно
    QWidget mainWindow;
    mainWindow.setWindowTitle("Красная кнопка");
    mainWindow.setFixedSize(300, 350);
    mainWindow.setStyleSheet("background-color: #e0e0e0;"); //  фон окна

    // 2. Создаем кнопку
    QPushButton *redButton = new QPushButton(&mainWindow);
    redButton->setFixedSize(200, 200); // Делаем её квадратной

    // 3. Задаем внешний вид кнопки (обычная и нажатая)
    redButton->setStyleSheet(
        // Стиль для обычной кнопки (круглая, красная, с рамкой)
        "QPushButton {"
        "   background-color: #ff0000;"
        "   border-style: solid;"
        "   border-width: 4px;"
        "   border-radius: 100px;" // Делаем круг из квадрата 200x200
        "   border-color: #be0000;"
        "}"
        // Стиль, когда кнопка НАЖАТА (становится темнее)
        "QPushButton:pressed {"
        "   background-color: #b30000;"
        "   border-color: #800000;"
        "}"
    );

    // 4. Настраиваем вертикальный компоновщик, чтобы отцентровать кнопку
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(redButton, 0, Qt::AlignCenter);
    mainWindow.setLayout(layout);

    // 5. Соединяем нажатие кнопки со стандартным системным звуком
    QObject::connect(redButton, &QPushButton::pressed, []() {
        QApplication::beep(); // Воспроизводит системный щелчок/сигнал
    });

    mainWindow.show();
    return app.exec();
}
