#include "mainwindow.h"
#include "ui_design.h"
#include <fstream>
#include <string>
#include <sstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    auto user = getenv("username");
    path = "C:\\users\\" + std::string(user) +"\\AppData\\Roaming\\";
    std::time_t t = std::time(NULL);
    struct tm tm = *localtime(&t);

    std::string file_path = path + month[tm.tm_mon + 1] + std::to_string(tm.tm_year + 1900) + ".txt";
    path = file_path;
    ui->montLabel->setText(QString::fromStdString(month[tm.tm_mon + 1] + ", " + std::to_string(tm.tm_year + 1900)));

    std::ifstream file(path);
    if(file.fail())
    {
        file.close();
        std::ofstream ff(path);
        ff.close();
        file.open(path);
    }

    std::string txt;
    while(std::getline(file, txt))
    {
        const QString str = QString::fromStdString(txt);
        auto pr = this->part_string(str);

        if(pr.second.isEmpty() or pr.first.isEmpty())
            continue;
        ui->listWidget->addItem(pr.first);
        ui->amtWidget->addItem(pr.second);
        spendings += pr.second.toInt();
        mapping.push_back(pr);
    }

    ui->textBrowser->setText(QString::number(spendings));
}

QPair<QString, QString> MainWindow::part_string(const QString &txt)
{
    QString intval;

    for(int i = txt.size()-1; i >= 0; i--)
    {
        if(!txt[i].isDigit())
            break;
        intval += txt[i];
    }

    std::reverse(intval.begin(), intval.end());
    auto first = QString::fromStdString(txt.toStdString().substr(0, txt.size()-intval.size()));
    auto sec = (intval);

    return {first, sec};
}


MainWindow::~MainWindow()
{
    ui->listWidget->selectAll();
    auto spendlist = ui->listWidget->selectedItems();
    ui->amtWidget->selectAll();
    auto amtlist = ui->amtWidget->selectedItems();
    std::ofstream file(path);

    foreach (auto it, spendlist) {
        std::pair<QString, QString> p ;
        p.first = it->text();
        mapping.push_back(p);
    }

    int i = 0;
    foreach (auto it, amtlist) {
        std::pair<QString, QString> p ;
        p.first = mapping.at(i).first;
        p.second = it->text();
        mapping.at(i) = p;
        i += 1;
    }

    for(auto && it : mapping)
    {
        auto txt = it.first + " " + it.second + "\n";
        file.write(txt.toStdString().c_str(), txt.size());
    }

    delete ui;
}


void MainWindow::on_addBtn_clicked()
{

    auto var = ui->expnseEdit->text();
    if(var.isEmpty())
        return;

    auto pair = this->part_string(var);

    if(pair.second.isEmpty())
        return;
    ui->listWidget->addItem(pair.first);
    ui->amtWidget->addItem(pair.second);
    spendings += pair.second.toInt();
    mapping.push_back(pair);
    ui->textBrowser->setText(QString::number(spendings));
    ui->expnseEdit->clear();
}


void MainWindow::on_delBtn_clicked()
{
    ui->amtWidget->clearSelection();
    auto val = ui->listWidget->currentIndex();
    auto pair = std::make_pair(ui->listWidget->currentItem()->text(), ui->amtWidget->item(val.row())->text());
    mapping.erase(std::find(mapping.begin(), mapping.end(), pair));

    delete ui->listWidget->currentItem();
    delete ui->amtWidget->item(val.row());
    spendings -= pair.second.toInt();
    ui->textBrowser->setText(QString::number(spendings));
    ui->listWidget->clearSelection();
    ui->amtWidget->clearSelection();
}


void MainWindow::on_closeBtn_clicked()
{
    this->~MainWindow();
}


void MainWindow::on_amtWidget_itemClicked(QListWidgetItem *item)
{
    ui->amtWidget->clearSelection();
}


void MainWindow::on_actionClear_Current_Month_Records_triggered()
{
    ui->listWidget->selectAll();
    ui->amtWidget->selectAll();
    ui->listWidget->clear();
    ui->amtWidget->clear();
    this->spendings = 0;
    ui->expnseEdit->setText(QString::number(this->spendings));
    mapping.clear();
}


void MainWindow::on_expnseEdit_returnPressed()
{
    this->on_addBtn_clicked();
}


void MainWindow::on_editBtn_clicked()
{
    auto val = ui->listWidget->currentIndex();

    auto pair = std::make_pair(ui->listWidget->currentItem()->text(), ui->amtWidget->item(val.row())->text());
    ui->expnseEdit->setText(pair.first + " " + pair.second);
    this->editFlag = true;
    ui->listWidget->currentItem()->setSelected(1);

}



