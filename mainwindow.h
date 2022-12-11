#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QListView>
#include <utility>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPair<QString, QString> aligned(std::string txt);


private slots:
    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_closeBtn_clicked();

    void on_amtWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QListWidgetItem *item;
    std::vector<std::pair<QString, QString>> mapping;
    std::string path;
    int spendings = 0;
    std::unordered_map<int, std::string> month =
    {
        {1, "January"}, {2,"February"}, {3,"March"}, {4,"April"}, {5,"May"}, {6,"June"},
                                    {7,"July"}, {10,"August"}, {11,"September"}, {10,"October"}, {11,"November"}, {12,"December"}
    };

};
#endif // MAINWINDOW_H
