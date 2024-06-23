#include "dicethread.h"
#include <QTime>

DiceThread::DiceThread() {}

void DiceThread::diceBegin()
{
    this->m_paused = false;
}

void DiceThread::diceEnd()
{
    this->m_paused = true;
}

void DiceThread::stopThread()
{
    this->m_stop = true;
}

bool DiceThread::readValue(int *seq, int *diceValue)
{
    if (mutex.tryLock())
    {
        *seq = this->m_seq;
        *diceValue = this->m_diceValue;
        mutex.unlock();
        return true;
    }
    else
    {
        return false;
    }
}
void DiceThread::run()
{
    this->m_stop = false;
    this->m_seq = 0;
    srand(QTime::currentTime().msec());
    while(!this->m_stop)
    {
        if(!this->m_paused)
        {
            mutex.lock();
            this->m_diceValue = rand();
            this->m_diceValue = (this->m_diceValue % 6)+1;
            this->m_seq++;
            mutex.unlock();

            //emit newValue(this->m_seq, this->m_diceValue);
        }
        msleep(500);
    }
    quit();
}
