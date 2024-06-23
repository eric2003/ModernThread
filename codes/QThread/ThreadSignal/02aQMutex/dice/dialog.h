#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

#include "dicethread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
protected:
    void    closeEvent(QCloseEvent *event);
private slots:
    void on_newValue(int seq, int diceValue);
    void onTimeOut();
    void on_threadA_Started();
    void on_threadA_Finished();
    void on_btnStartThread_clicked();
    void on_btnStopThread_clicked();

    void on_btnDiceBegin_clicked();

    void on_btnDiceEnd_clicked();

    void on_btnClear_clicked();

private:
    Ui::Dialog *ui;
private:
    DiceThread   threadA;
    QTimer  mTimer;
    int mSeq,mDiceValue;
};
#endif // DIALOG_H
