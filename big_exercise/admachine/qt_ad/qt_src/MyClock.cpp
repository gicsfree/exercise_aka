#include "MyClock.h"

MyClock::MyClock(QWidget *parent)
  :QLCDNumber(parent)
{
    setGeometry(600, 0, 200, 100);
    setSegmentStyle(Filled);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(displayTime()));
    timer->start(1000);
}

void MyClock::displayTime()
{
    QString time = QTime::currentTime().toString("hh:mm:ss");
    setNumDigits(8);
    display(time);
}
