#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QGraphicsBlurEffect>
#include <QPixmap>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1.  главное окно
    QWidget mainWindow;
    mainWindow.setWindowTitle("Blur Effect App");
    mainWindow.resize(500, 600);

    // 2. три виджета
    QLabel *imageLabel = new QLabel(&mainWindow);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("Картинка не выбрана");
    // Чтобы текст или картинка не сжимали окно
    imageLabel->setMinimumSize(400, 400);

    QSlider *blurSlider = new QSlider(Qt::Horizontal, &mainWindow);
    blurSlider->setRange(0, 100); // Ограничение мин 0, макс 10
    blurSlider->setValue(0);

    QPushButton *openButton = new QPushButton("Open", &mainWindow);

    // 3. Располагаем виджеты вертикально друг под другом
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(imageLabel);
    layout->addWidget(blurSlider);
    layout->addWidget(openButton);
    mainWindow.setLayout(layout);

    // 4. Создаем эффект размытия и применяем его
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(&mainWindow);
    blurEffect->setBlurRadius(0); // Изначально размытия нет
    imageLabel->setGraphicsEffect(blurEffect);

    // Переменная для хранения оригинальной картинки
    // Используем std::shared_ptr, чтобы безопасно передавать в лямбда-функции
    auto sourcePixmap = std::make_shared<QPixmap>();

    // 5. кнопка "Open" —  выбор файла JPG
    QObject::connect(openButton, &QPushButton::clicked, [&mainWindow, imageLabel, blurSlider, blurEffect, sourcePixmap]() {
        QString filePath = QFileDialog::getOpenFileName(&mainWindow,
            "Выберите изображение", "", "Изображения (*.jpg *.jpeg)");

        if (!filePath.isEmpty()) {
            if (sourcePixmap->load(filePath)) {
                // Подгоняем под размеры с сохранением пропорций
                imageLabel->setPixmap(sourcePixmap->scaled(
                    imageLabel->width(),
                    imageLabel->height(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                ));
                // При открытии новой картинки сбрасываем слайдер в 0
                blurSlider->setValue(0);
                blurEffect->setBlurRadius(0);
            }
        }
    });

    // 6. слайдер— изменение глубины Blur при перемещении ползунка
    QObject::connect(blurSlider, &QSlider::valueChanged, [blurEffect](int newValue) {
        // радиус размытия от 0 до 10
        blurEffect->setBlurRadius(newValue);
    });

    mainWindow.show();
    return app.exec();
}
