#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QListView>
#include <utility>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPair<QString, QString> part_string(const QString &txt);

private slots:
    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_closeBtn_clicked();

    void on_amtWidget_itemClicked(QListWidgetItem *item);

    void on_actionClear_Current_Month_Records_triggered();


    void on_expnseEdit_returnPressed();

    void on_editBtn_clicked();


    void on_actionGet_by_MM_YY_triggered();

private:
    Ui::MainWindow *ui;

    std::vector<std::pair<QString, QString>> mapping;
    std::string path;
    bool editFlag = false;
    int spendings = 0;
    std::unordered_map<int, std::string> month =
    {
        {1, "January"}, {2,"February"}, {3,"March"}, {4,"April"}, {5,"May"}, {6,"June"},
        {7,"July"}, {10,"August"}, {11,"September"}, {10,"October"}, {11,"November"}, {12,"December"}
    };

};

#endif // MAINWINDOW_H
