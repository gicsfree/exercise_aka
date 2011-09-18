#include "MyMessage.h"

MyMessage::MyMessage(QWidget *parent)
  :QLabel(parent)
{
    /* message背景图片 */
    setGeometry(0, 500, 800, 100);
    QPixmap *bgPicture = new QPixmap("./images/tomandjerry.jpg");
    setPixmap(bgPicture->scaled(width(), height()));

    /* message label */
    x = 799;
    msgLabel = new QLabel(parent);
    msgLabel->setGeometry(0, 500, 800, 100);

    /* 设置字体：绿色、FreeMono字体、80号 */
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::green);
    msgLabel->setPalette(pe);
    msgLabel->setFont(QFont(QString::fromUtf8("hwls"), 40));

    /* 定时器 */
    QTimer *timer = new QTimer(parent);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(displayMessage()));
    timer->start(10);
}

void MyMessage::setMsg(QString msg)
{
    msgLabel->setText(msg);
    msgLen = msgLabel->fontMetrics().width(msgLabel->text());
}

void MyMessage::displayMessage()
{
    x--;
    if ((x + msgLen) <= 0)
    {
        x = 799;
    }
    msgLabel->setGeometry(x, 500, msgLen, 100);
}
