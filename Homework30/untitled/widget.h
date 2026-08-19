#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // Автоматические слоты Qt
    void on_btn_add_clicked();
    void on_btn_sub_clicked();
    void on_btn_mul_clicked();
    void on_btn_div_clicked();

private:
    Ui::Widget *ui;

    // Метод вычислений
    void calculate(char operation);
};
