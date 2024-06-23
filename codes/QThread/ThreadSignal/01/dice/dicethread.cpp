#include "dicethread.h"
#include <QTime>

DiceThread::DiceThread() {}

void DiceThread::diceBegin()
{
    this->m_Paused = false;

}

void DiceThread::dicePause()
{
    this->m_Paused = true;
}

void DiceThread::stopThread()
{
    this->m_stop = true;
}

void DiceThread::run()
{
    this->m_stop = false;
    this->m_seq = 0;
    srand(QTime::currentTime().msec());
    while(!this->m_stop)
    {
        if(!this->m_Paused)
        {
            this->m_diceValue = rand();
            this->m_diceValue = (this->m_diceValue % 6)+1;
            this->m_seq++;
            emit newValue(this->m_seq, this->m_diceValue);
        }
        msleep(500);
    }
    quit();
}
