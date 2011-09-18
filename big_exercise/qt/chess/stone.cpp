#include "stone.h"

myForm *stone::palate; //给静态成员分配储存空间

stone::stone(int id, int type, stone::scolor_t red, QWidget *parent)
  :QWidget(parent), m_id(id), m_type(type), m_red(red), m_killed(false), m_selected(0)
{
    qDebug() << "my stone" << endl;
    switch (m_id)
    {
        case 0:
            stone_pos.setX(1);
            stone_pos.setY(1);
            this->setGeometry(30, 30, 60, 60); //设置窗体区域
            break;

        case 1:
            stone_pos.setX(2);
            stone_pos.setY(1);
            this->setGeometry(90, 30, 60, 60);
            break;

        case 2:
            stone_pos.setX(3);
            stone_pos.setY(1);
            this->setGeometry(150, 30, 60, 60);
            break;

        default:
             break;
    }
    update();
}

void stone::paintEvent(QPaintEvent *)
{  
    qDebug() << "stone PaintEvent()" << endl;

    QPainter painter(this);

    QFont font("ZYSong18030", 30, QFont::Light);
    painter.setFont(font);

    QPen pen(Qt::SolidLine);
    if (m_red == stone::RED)
    {
        pen.setColor(Qt::red);
    }
    else
    {
        pen.setColor(Qt::black);
    }
    painter.setPen(pen);

    if (m_selected == 1)
    {
        painter.setBrush(QBrush(Qt::blue));
    }
    else
    {
        painter.setBrush(QBrush(Qt::yellow));
    }

    switch (m_type)
    {
        case 0:
            painter.drawEllipse(rect()); //rect()可得到窗体大小
            painter.drawText(rect(), QString::fromUtf8("车"), Qt::AlignHCenter | Qt::AlignVCenter);
            break;    

        case 1:
            painter.drawEllipse(rect());
            painter.drawText(rect(), QString::fromUtf8("马"), Qt::AlignHCenter | Qt::AlignVCenter);
            break;  

        case 2:
            painter.drawEllipse(rect());
            painter.drawText(rect(), QString::fromUtf8("象"), Qt::AlignHCenter | Qt::AlignVCenter);
            break; 

        default:
            break;
    }
}

void stone::mousePressEvent(QMouseEvent *)
{
    qDebug() << "you clicked stone position(" << stone_pos << ")" << endl;
//    qDebug() << "width: " << geometry().width() << endl;
//    qDebug() << "height: " << geometry().height() << endl;

    int tmpid = stone::palate->get_selectedid(); //静态成员使用方法
    if (tmpid != -1 && stone::palate->s[tmpid]->m_selected == 1)
    {
        stone::palate->s[tmpid]->m_selected = 0;
        stone::palate->s[tmpid]->update();
    }

    m_selected = 1;
    stone::palate->set_selectedid(m_id);
    this->update();
}
