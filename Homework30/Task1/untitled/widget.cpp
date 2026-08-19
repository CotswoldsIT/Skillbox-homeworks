#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::calculate(char operation) {
    bool ok1, ok2;

    // проверка текста
    double num1 = ui->lineEdit_1->text().toDouble(&ok1);
    double num2 = ui->lineEdit_2->text().toDouble(&ok2);

    // Если ввели буквы или оставили поле пустым — вывести ERROR
    if (!ok1 || !ok2) {
        ui->label_result->setText("ERROR");
        return;
    }

    double result = 0;

    if (operation == '+') {
        result = num1 + num2;
    } else if (operation == '-') {
        result = num1 - num2;
    } else if (operation == '*') {
        result = num1 * num2;
    } else if (operation == '/') {
        // Проверка деления на ноль
        if (num2 == 0) {
            ui->label_result->setText("ERROR");
            return;
        }
        result = num1 / num2;
    }

    // Вывод результата на экран
    ui->label_result->setText(QString::number(result));
}

// Связываем клики покнопкам с методом подсчета
void Widget::on_btn_add_clicked() { calculate('+'); }
void Widget::on_btn_sub_clicked() { calculate('-'); }
void Widget::on_btn_mul_clicked() { calculate('*'); }
void Widget::on_btn_div_clicked() { calculate('/'); }
