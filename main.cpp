#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Expense Manager");
    QIcon ic("C:\\Your\\Address\\To\\A\\PNG\\Logo.png");
    if(!ic.isNull())
        w.setWindowIcon(ic);
    w.show();
    return a.exec();
}
