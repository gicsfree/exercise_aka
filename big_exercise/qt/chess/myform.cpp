#include "myform.h"
#include "stone.h"

myForm::myForm(QWidget *parent)
  :QWidget(parent), x_start(60), y_start(60), len(60), m_selectedid(-1)
{
    stone::palate = this; //使stone的静态指针指向myform
    for (int i = 0; i < 3; i++)
    {
        s[i] = new stone(i, i, stone::RED, this); //初始化stone对象
    }
}

void myForm::paintEvent(QPaintEvent *) //void QWidget::paintEvent ( QPaintEvent * event )   [virtual protected]
{ 
    qDebug() << "table paintEvent()" << endl;

    QPainter painter(this); //只做局部变量, 对应this窗体

    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);

    for (int i = 0; i < 10; i++)
    {
        painter.drawLine(QPoint(x_start, y_start + len * i), QPoint(x_start + len * 8, y_start + len * i));
    }

    for (int i = 0; i < 9; i++)
    {
        if ((i == 0) || (i == 8))
        {
            painter.drawLine(QPoint(x_start + len * i, y_start), QPoint(x_start + len * i, y_start + len * 9));
        }
        else
        {
            painter.drawLine(QPoint(x_start + len * i, y_start), QPoint(x_start + len * i, y_start + len * 4));
            painter.drawLine(QPoint(x_start + len * i, y_start + len * 5), QPoint(x_start + len * i, y_start + len * 9));
        }
    }

    painter.drawLine(QPoint(x_start + len * 3, y_start), QPoint(x_start + len * 5, y_start + len * 2));
    painter.drawLine(QPoint(x_start + len * 3, y_start + len * 2), QPoint(x_start + len * 5, y_start));

    painter.drawLine(QPoint(x_start + len * 3, y_start + len * 7), QPoint(x_start + len * 5, y_start + len * 9));
    painter.drawLine(QPoint(x_start + len * 3, y_start + len * 9), QPoint(x_start + len * 5, y_start + len * 7));

    QFont font("ZYSong18030", 45, QFont::Light);
    painter.setFont(font);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    painter.translate(QPoint(x_start + len * 2, y_start + len * 5));
    painter.rotate(-90);
    painter.drawText(0, 0, QString::fromUtf8("楚"));
    painter.rotate(90);
    painter.translate(QPoint(-(x_start + len * 2), -(y_start + len * 5)));

    painter.translate(QPoint(x_start + len * 3, y_start + len * 5));
    painter.rotate(-90);
    painter.drawText(0, 0, QString::fromUtf8("河"));
    painter.rotate(90);
    painter.translate(QPoint(-(x_start + len * 3), -(y_start + len * 5)));

    painter.translate(QPoint(x_start + len * 6, y_start + len * 4));
    painter.rotate(90);
    painter.drawText(0, 0, QString::fromUtf8("汉"));
    painter.rotate(-90);
    painter.translate(QPoint(-(x_start + len * 6), -(y_start + len * 4)));

    painter.translate(QPoint(x_start + len * 5, y_start + len * 4));
    painter.rotate(90);
    painter.drawText(0, 0, QString::fromUtf8("界"));
    painter.rotate(-90);
    painter.translate(QPoint(-(x_start + len * 5), -(y_start + len * 4)));

#if 0
    painter.translate(QPoint(x_start + len * 2, y_start + len * 5));
    painter.rotate(-90);
    painter.drawText(0, 0, QString::fromUtf8("楚"));
    painter.rotate(90);
    painter.translate(QPoint(-(x_start + len * 2), -(y_start + len * 5)));

    painter.translate(QPoint(x_start + len * 3, y_start + len * 5));
    painter.rotate(-90);
    painter.drawText(0, 0, QString::fromUtf8("河"));
    painter.rotate(90);
    painter.translate(QPoint(-(x_start + len * 3), -(y_start + len * 5)));

    painter.translate(QPoint(x_start + len * 6, y_start + len * 4));
    painter.rotate(90);
    painter.drawText(0, 0, QString::fromUtf8("汉"));
    painter.rotate(-90);
    painter.translate(QPoint(-(x_start + len * 6), -(y_start + len * 4)));

    painter.translate(QPoint(x_start + len * 5, y_start + len * 4));
    painter.rotate(90);
    painter.drawText(0, 0, QString::fromUtf8("界"));
    painter.rotate(-90);
    painter.translate(QPoint(-(x_start + len * 5), -(y_start + len * 4)));
#endif
}

void myForm::mousePressEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    int x = (p.x() + 30) / 60;
    int y = (p.y() + 30) / 60;
    
    QPoint clicked_pos;
    clicked_pos.setX(x);
    clicked_pos.setY(y);

    if (m_selectedid != -1)
    {
        if (canMove(m_selectedid, clicked_pos))
        {
            s[m_selectedid]->setGeometry(clicked_pos.x() * 60 - 30, clicked_pos.y() * 60 - 30, 60, 60);
            s[m_selectedid]->stone_pos = clicked_pos;
            s[m_selectedid]->update();
        }
    }

    qDebug() << "you clicked table position(" << clicked_pos << ")" << endl;

//    qDebug() << "you clicked position(" << event->pos().x() << ", " << event->pos().y() << ")" << endl;
//    qDebug() << "width: " << geometry().width() << endl;
//    qDebug() << "height: " << geometry().height() << endl;
}

bool myForm::canMove(int cur_id, QPoint &to_pos)
{
    int dx, dy;
    int mytype = s[cur_id]->get_type();

    if (to_pos.x() > 9 || to_pos.x() < 1)
        return false;
    if (to_pos.y() > 10 || to_pos.y() < 1)
        return false;

    switch (mytype)
    {
        case 1:
            dx = s[cur_id]->stone_pos.x() - to_pos.x();
            dx = abs(dx);
            dy = s[cur_id]->stone_pos.y() - to_pos.y();
            dy = abs(dy);
            int result = dx * 10 + dy;
            if (result == 21 || result == 12)
                return true;
            else
                return false;
            break;
    }

    return true;
}
