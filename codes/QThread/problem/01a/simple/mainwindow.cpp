#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int i = 0;
    while(true)
    {
        this->ui->lcdNumber->display(QString::number(i++));
        std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    }
}

