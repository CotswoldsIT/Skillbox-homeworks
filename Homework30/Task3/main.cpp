#include "remote.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Remote w;
    w.setWindowTitle("ТВ Пульт");
    w.setFixedSize(240, 680); // размеры
    w.show();
    return app.exec();
}
