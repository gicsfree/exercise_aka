#include <QTime>
#include <QTimer>
#include "clock.h"

myClock::myClock(QWidget *parent)
:QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    QTimer *timer = new QTimer(parent);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(show_time()));
    timer->start(1000);
}

void myClock::show_time()
{
    QString time = QTime::currentTime().toString("hh:mm:ss");
    setNumDigits(8);
    display(time);
}
