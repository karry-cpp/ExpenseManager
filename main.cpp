#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Expense Manager");
    QIcon ic("C:\\Users\\kunal\\Desktop\\logo.png");
    w.setWindowIcon(ic);
    w.show();
    return a.exec();
}
