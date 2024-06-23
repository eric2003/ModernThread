#ifndef DICETHREAD_H
#define DICETHREAD_H

#include <QObject>
#include <QThread>

class DiceThread : public QThread
{
    Q_OBJECT
public:
    DiceThread();
public:
    void diceBegin();
    void dicePause();
    void stopThread();
signals:
    void newValue(int seq, int diceValue);
protected:
    void run() override;
private:
    int m_seq = 0;
    int m_diceValue;
    bool m_Paused = true;
    bool m_stop = false;


};

#endif // DICETHREAD_H
