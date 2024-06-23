#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>

class MyTask : public QObject
{
    Q_OBJECT
public:
    explicit MyTask(QObject *parent = nullptr);
public:
    void task01();
    void task02();
signals:
    void signalTask01(int value);
    void signalTask02(int value);
};

#endif // MYTASK_H
