#include "widget.h"
#include "./ui_widget.h"
#include "mytask.h"
#include <QThread>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->task1 = new MyTask();
    this->th1 = new QThread(this);
    this->task1->moveToThread(this->th1);
    //this->th1->start();

    this->task2 = new MyTask();
    this->th2 = new QThread(this);
    this->task2->moveToThread(this->th2);
    //this->th2->start();

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this->task1,&MyTask::task01);
    QObject::connect(this->task1,&MyTask::signalTask01,[=](int value){
        this->ui->lcdNumber->display(QString::number(value));
    });

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this->task2,&MyTask::task02);
    QObject::connect(this->task2,&MyTask::signalTask02,[=](int value){
        this->ui->lcdNumber_2->display(QString::number(value));
    });
}

Widget::~Widget()
{
    this->th1->terminate();
    this->th2->terminate();
    delete this->task1;
    delete this->task2;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    this->th1->start();
    this->th2->start();
}

