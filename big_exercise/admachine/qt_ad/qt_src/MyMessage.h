#ifndef MYMESSAGE_H
#define MYMESSAGE_H

#include<QtGui>

class MyMessage: public QLabel
{
    Q_OBJECT

public:
    MyMessage(QWidget *parent = 0);
    void setMsg(QString);

private slots:
    void displayMessage();

private:
    int x;
    int msgLen;
    QLabel *msgLabel;
};

#endif // MYMESSAGE_H
