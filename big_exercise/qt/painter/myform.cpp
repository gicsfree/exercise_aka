#include "myform.h"

myForm::myForm(QWidget *parent)
  :QWidget(parent)
{

}

void myForm::paintEvent(QPaintEvent *event) //void QWidget::paintEvent ( QPaintEvent * event )   [virtual protected]
{
    QWidget::paintEvent(event);   
    qDebug() << "my PaintEvent()" << endl;

    QPainter painter(this); //只做局部变量, 对应this窗体

     //设置笔
    QPen pen(Qt::DashDotLine);
    //pen.setColor(QColor(255, 0, 255)); //QColor(255, 0, 255) is red 
    pen.setColor(Qt::red); //Qt::red在QColor类的最下方，有介绍

     //设置填充色
    QBrush brush(Qt::green, Qt::HorPattern);
    //brush.setStyle(Qt::HorPattern);

     //线性渐变填充
    QLinearGradient lg(60, 60, 160, 160); // 渐变颜色的设置方法
    lg.setColorAt(0, Qt::white);
    lg.setColorAt(0.2, Qt::blue);
    lg.setColorAt(0.4, Qt::green);
    lg.setColorAt(0.6, Qt::yellow);
    lg.setColorAt(0.8, QColor(218, 21, 166));
    lg.setColorAt(1, Qt::black);

     //线性渐变填充
    QLinearGradient lg1(260, 60, 360, 60);
    lg1.setColorAt(0, Qt::white);
    lg1.setColorAt(0.2, Qt::blue);
    lg1.setColorAt(0.4, Qt::green);
    lg1.setColorAt(0.6, Qt::yellow);
    lg1.setColorAt(0.8, QColor(218, 21, 166));
    lg1.setColorAt(1, Qt::black);
    QBrush brush1(lg1);

    //圆形渐变填充
    QRadialGradient rg(510, 110, 70, 460, 110);
    //QRadialGradient rg(510, 110, 70, 510, 110);
    rg.setColorAt(0, Qt::white);
    rg.setColorAt(0.2, Qt::blue);
    rg.setColorAt(0.4, Qt::green);
    rg.setColorAt(0.6, Qt::yellow);
    rg.setColorAt(0.8, QColor(218, 21, 166));
    rg.setColorAt(1, Qt::black);

    //圆锥渐变填充
    QConicalGradient cg(QPoint(110, 250), 30);
    cg.setColorAt(0, Qt::white);
    cg.setColorAt(0.1, Qt::blue);
    cg.setColorAt(0.3, Qt::green);
    cg.setColorAt(0.5, Qt::yellow);
    cg.setColorAt(0.7, QColor(218, 21, 166));
    cg.setColorAt(0.9, Qt::black);
    cg.setColorAt(1, Qt::white);

    painter.setPen(pen);

    painter.drawLine(0, 0, 60, 60);

    //painter.setBrush(brush);
    painter.setBrush(lg);
    painter.drawRect(60, 60, 100, 100);

    painter.setBrush(lg1);
    painter.drawRect(260, 60, 100, 100);

    painter.setBrush(rg);
    painter.drawRect(460, 60, 100, 100);

    painter.setBrush(cg);
    painter.drawEllipse(QRect(60, 200, 100, 100));

    painter.setBrush(brush);
    painter.drawEllipse(QRect(160, 200, 100, 100));

    QPixmap pix;
    pix.load("./1.png");
    painter.setBrush(pix);
    painter.drawEllipse(QRect(260, 200, 100, 100));

    painter.drawPixmap(360, 200, pix);

    pix = pix.scaled(pix.width() * 2, pix.height() * 2, Qt::KeepAspectRatio);
    painter.drawPixmap(460, 200, pix);

    painter.translate(QPoint(660, 200));
    painter.rotate(90); //改坐标系更替，原先画好的东西不变，只改变之后的操作
    painter.drawPixmap(0, 0, pix);

    painter.rotate(-90);
    painter.translate(QPoint(-660, -200));
    painter.drawPixmap(660, 200, pix);

    QFont font("文泉驿正黑", 50, QFont::Bold, true);
    painter.setFont(font);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    painter.drawText(760, 300, QString::fromUtf8(">你好"));
}

void myForm::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "you clicked position(" << event->pos().x() << ", " << event->pos().y() << ")" << endl;
    qDebug() << "width: " << geometry().width() << endl;
    qDebug() << "height: " << geometry().height() << endl;
}
