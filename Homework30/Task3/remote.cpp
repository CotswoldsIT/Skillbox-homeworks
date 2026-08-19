#include "remote.h"
#include "./ui_remote.h"
#include <QPushButton>

Remote::Remote(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Remote)
{
    ui->setupUi(this);
    updateDisplay(); // начальное состояние

    // Собираем все кнопки
    const QList<QPushButton*> numButtons = {
        ui->btn_0, ui->btn_1, ui->btn_2, ui->btn_3, ui->btn_4,
        ui->btn_5, ui->btn_6, ui->btn_7, ui->btn_8, ui->btn_9
    };

    for (QPushButton* btn : numButtons) {
        connect(btn, &QPushButton::clicked, this, &Remote::onNumberClicked);
    }
}

Remote::~Remote() {
    delete ui;
}

// При нажатии на любую цифру берем её текст и ставим как канал
void Remote::onNumberClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        mCurrentChannel = button->text().toInt();
        updateDisplay();
    }
}

// Переключение каналов вперед
void Remote::on_btn_ch_up_clicked() {
    mCurrentChannel++;
    if (mCurrentChannel > 99) mCurrentChannel = 0;
    updateDisplay();
}

// Переключение каналов назад
void Remote::on_btn_ch_down_clicked() {
    mCurrentChannel--;
    if (mCurrentChannel < 0) mCurrentChannel = 99;
    updateDisplay();
}

// Увеличение громкости на 10%
void Remote::on_btn_vol_up_clicked() {
    mCurrentVolume += 10;
    if (mCurrentVolume > 100) mCurrentVolume = 100;
    updateDisplay();
}

// Уменьшение громкости на 10%
void Remote::on_btn_vol_down_clicked() {
    mCurrentVolume -= 10;
    if (mCurrentVolume < 0) mCurrentVolume = 0;
    updateDisplay();
}

// Отображение текущего статуса
void Remote::updateDisplay() {
    QString status = QString("Канал: %1\nГромкость: %2%")
                     .arg(mCurrentChannel)
                     .arg(mCurrentVolume);
    ui->label_display->setText(status);
}
