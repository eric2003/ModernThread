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

void MainWindow::display()
{
    int i = 0;
    while(true)
    {
        this->ui->lcdNumber->display(QString::number(i++));
        qDebug() << "i=" << i;
        std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    }
}

void MainWindow::on_pushButton_clicked()
{
    std::thread th( &MainWindow::display, this );
    th.join();
}

