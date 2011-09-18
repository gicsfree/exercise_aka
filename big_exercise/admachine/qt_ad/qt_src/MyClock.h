#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <QtGui>

class MyClock: public QLCDNumber
{
    Q_OBJECT

public:
    MyClock(QWidget *parent = 0);

private slots:
    void displayTime();
};

#endif

