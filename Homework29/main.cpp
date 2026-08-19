#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QSize>

// виджет для отображения круга
class ColorfulCircle : public QWidget {
private:
    QPixmap mCurrentCircle;  // Текущая отображаемая картинка
    QPixmap mGreenCircle;   // Зеленый круг
    QPixmap mYellowCircle;  // Желтый круг
    QPixmap mRedCircle;     // Красный круг

public:
    ColorfulCircle(QWidget *parent = nullptr) : QWidget(parent) {
        // Загружаем файлы картинок из папки приложения
        mGreenCircle.load("green.png");
        mYellowCircle.load("yellow.png");
        mRedCircle.load("red.png");

        // Стартовый цвет при запуске — зеленый
        mCurrentCircle = mGreenCircle;
    }

    //  смен цвета и обновления экрана
    void setGreen() {
        mCurrentCircle = mGreenCircle;
        update(); //
    }

    void setYellow() {
        mCurrentCircle = mYellowCircle;
        update();
    }

    void setRed() {
        mCurrentCircle = mRedCircle;
        update();
    }

protected:
    //  минимальный рекомендуемый размер для компоновщика
    QSize minimumSizeHint() const override {
        return QSize(100, 100);
    }

    //  отрисовка картинки внутри нашего виджета
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);

        if (!mCurrentCircle.isNull()) {
            // подгонка круга под размеры окна с сохранением пропорций
            painter.drawPixmap(rect(), mCurrentCircle.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Главное окно программы с фиксированными размерами
    QWidget mainWindow;
    mainWindow.setWindowTitle("Colorful Circle");
    mainWindow.setFixedSize(200, 250);

    // объекты круга и горизонтального ползунка
    ColorfulCircle *circle = new ColorfulCircle(&mainWindow);
    QSlider *slider = new QSlider(Qt::Horizontal, &mainWindow);

    // диапазон от 0 до 99
    slider->setRange(0, 99);

    // круг и ползунок вертикально друг под другом
    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    layout->addWidget(circle);
    layout->addWidget(slider);
    mainWindow.setLayout(layout);

    // привязка ползунка со сменой цвета круга
    QObject::connect(slider, &QSlider::valueChanged, [circle](int newValue) {
        if (newValue <= 33) {
            circle->setGreen();
        } else if (newValue <= 66) {
            circle->setYellow();
        } else {
            circle->setRed();
        }
    });

    mainWindow.show();
    return app.exec();
}
