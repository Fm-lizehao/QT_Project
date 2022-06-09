#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    main_timer.setInterval(1);
    main_timer.start();
    return a.exec();
}
