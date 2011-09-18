#include <QPixmap>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include "mainForm.h"
#include "logo.h"
#include "clock.h"
#include "picturedisplay.h"
#include "message.h"

MainForm::MainForm(QWidget *parent)
:QDialog(parent)
{
    pic = new myPicture(this);
    message = new MyMessage(this);
    //message->setMessage(QString::fromUtf8("迪斯尼世界欢迎您！ Welcome to Disneyworld!"));
    myForm();
    message->setMsg(QString::fromUtf8("迪斯尼世界欢迎您！ Welcome to Disneyworld!"));
    MyLogo *logo = new MyLogo(this);

    myClock *clock = new myClock(this);
    clock->setGeometry(630,70, 100, 50);
    clock->setFrameShape(QFrame::NoFrame);
    clock->show();  
}

void MainForm::myForm()
{
    /* 视频黑色背景 */
    QLabel *label_vedio = new QLabel(this);
    label_vedio->setGeometry(0, 0, 560, 400);
    label_vedio->setAutoFillBackground (true);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    label_vedio->setPalette(pal);

    /* 主窗体框 */
    QLabel *label_mainForm = new QLabel(this);
    QString filename = QString::fromUtf8("./system_picture/mainform.png");
    QPixmap *mypic = new QPixmap(filename);
    label_mainForm->setPixmap(*mypic);
    label_mainForm->setGeometry(0, 0, mypic->width(), mypic->height());
    this->setGeometry(0, 0, mypic->width(), mypic->height());
}
