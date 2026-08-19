#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Remote; }
QT_END_NAMESPACE

class Remote : public QWidget {
    Q_OBJECT

public:
    Remote(QWidget *parent = nullptr);
    ~Remote();

private slots:
    void onNumberClicked();       // Слот для кнопок 0-9
    void on_btn_ch_up_clicked();   // Канал +
    void on_btn_ch_down_clicked(); // Канал -
    void on_btn_vol_up_clicked();  // Громкость +
    void on_btn_vol_down_clicked();// Громкость -

private:
    Ui::Remote *ui;
    int mCurrentChannel = 1;  // Стартовый канал
    int mCurrentVolume = 30;  // Стартовая громкость (30%)

    void updateDisplay();     // Функция обновления мини-экрана пульта
};
