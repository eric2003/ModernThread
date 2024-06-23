#include "mythread.h"
#include <QDebug>

MyThread::MyThread() {}

void MyThread::run()
{
    int i = 0;
    while(true)
    {
        qDebug() << "i=" << i;
        emit myThreadSignal(i++);
        std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
    }
}
