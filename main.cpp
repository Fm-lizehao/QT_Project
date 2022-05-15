#include "global.h"

#include "mainwindow.h"

QTimer main_timer;

QFont standard_font("幼圆",15,QFont::Bold,false);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    main_timer.setInterval(17);
    main_timer.start();
    return a.exec();
}
