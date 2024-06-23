#ifndef DICETHREAD_H
#define DICETHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>

class DiceThread : public QThread
{
    Q_OBJECT
public:
    DiceThread();
public:
    void diceBegin();
    void diceEnd();
    void stopThread();
    bool readValue(int *seq, int *diceValue);
signals:
    void newValue(int seq, int diceValue);
protected:
    void run() override;
private:
    QMutex  mutex;
    int m_seq = 0;
    int m_diceValue;
    bool m_paused = true;
    bool m_stop = false;


};

#endif // DICETHREAD_H
