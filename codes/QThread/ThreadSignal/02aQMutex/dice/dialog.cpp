#include "dialog.h"
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QObject::connect(&this->threadA,&QThread::started,this,&Dialog::on_threadA_Started);
    QObject::connect(&this->threadA,&QThread::finished,this,&Dialog::on_threadA_Finished);
    //QObject::connect(&threadA,&DiceThread::newValue,this,&Dialog::on_newValue);
    QObject::connect(&this->mTimer,&QTimer::timeout,this,&Dialog::onTimeOut);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if (this->threadA.isRunning())
    {
        this->threadA.stopThread();
        this->threadA.wait();
    }
    event->accept();
}

void Dialog::on_newValue(int seq, int diceValue)
{
    QString  str=QString::asprintf("第 %d 次掷骰子，点数为：%d",seq,diceValue);
    ui->plainTextEdit->appendPlainText(str);

    QPixmap pic; //图片显示
    QString filename=QString::asprintf(":/mydice/images/d%d.jpg",diceValue);
    pic.load(filename);
    ui->LabPic->setPixmap(pic);
}

void Dialog::onTimeOut()
{
    int tmpSeq=0,tmpValue=0;
    bool  valid = this->threadA.readValue(&tmpSeq,&tmpValue);

    if (valid && (tmpSeq!=mSeq)) //有效，并且是新数据
    {
        mSeq=tmpSeq;
        mDiceValue=tmpValue;
        QString  str=QString::asprintf("第 %d 次掷骰子，点数为：%d",mSeq,mDiceValue);
        ui->plainTextEdit->appendPlainText(str);
        QPixmap pic;
        QString filename=QString::asprintf(":/mydice/images/d%d.jpg",mDiceValue);
        pic.load(filename);
        ui->LabPic->setPixmap(pic);
    }
}
void Dialog::on_threadA_Started()
{
    this->ui->LabA->setText("Thread状态：thread started");

}

void Dialog::on_threadA_Finished()
{
    this->ui->LabA->setText("Thread状态：thread finished");
}

void Dialog::on_btnStartThread_clicked()
{
    this->mSeq = 0;
    this->threadA.start();

    this->ui->btnStartThread->setEnabled(false);
    this->ui->btnStopThread->setEnabled(true);

    this->ui->btnDiceBegin->setEnabled(true);
    this->ui->btnDiceEnd->setEnabled(false);
}


void Dialog::on_btnStopThread_clicked()
{
    this->threadA.stopThread();//结束线程的run()函数执行
    this->threadA.wait();//

    this->ui->btnStartThread->setEnabled(true);
    this->ui->btnStopThread->setEnabled(false);

    this->ui->btnDiceBegin->setEnabled(false);
    this->ui->btnDiceEnd->setEnabled(false);
}


void Dialog::on_btnDiceBegin_clicked()
{
    this->threadA.diceBegin();
    this->mTimer.start(100);
    this->ui->btnDiceBegin->setEnabled(false);
    this->ui->btnDiceEnd->setEnabled(true);
}


void Dialog::on_btnDiceEnd_clicked()
{
    this->threadA.diceEnd();
    this->mTimer.stop();
    this->ui->btnDiceBegin->setEnabled(true);
    this->ui->btnDiceEnd->setEnabled(false);
}


void Dialog::on_btnClear_clicked()
{
    this->ui->plainTextEdit->clear();
}

