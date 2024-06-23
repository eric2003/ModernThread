#include "widget.h"
#include "./ui_widget.h"
#include "mythread.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->myThread = new MyThread();
    QObject::connect(this->myThread, &MyThread::myThreadSignal, [&](int value){
        this->ui->lcdNumber->display(QString::number(value));
    } );
}

Widget::~Widget()
{
    delete ui;
    this->myThread->quit();
    this->myThread->wait();
    delete this->myThread;
}

void Widget::on_MyButton_clicked()
{
    this->myThread->start();
}

