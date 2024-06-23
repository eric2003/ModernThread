#include "mytask.h"
#include <QDebug>
#include <thread>

MyTask::MyTask(QObject *parent)
    : QObject{parent}
{}

void MyTask::task01()
{
    int i = 0;
    while(true)
    {
        qDebug() << "i01=" << i;
        emit signalTask01(i++);
        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }

}

void MyTask::task02()
{
    int i = 100;
    while(true)
    {
        qDebug() << "i02=" << i;
        emit signalTask02(i++);
        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }
}
