#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>
#include <QTcpServer>
#include <QTcpSocket>
#include "ShowVideo.h"
#include "MyPicture.h"
#include "MyClock.h"
#include "MyMessage.h"
#include "DisplayPicture.h"

class MyWidget: public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = 0);

public slots:
    void accept(); //当客户端连接时，接受链接
    void process(); //当客户端发来数据时，处理数据

private:
    ShowVideo *myShowVideo;
    MyPicture *myPicture;
    MyClock *myClock;
    MyMessage *myMessage;
    DisplayPicture *myDisplayPicture;

    QTcpServer *server;
    QTcpSocket *socket;
    QByteArray data;

    QProcess *myProcess;

    QLabel *bgLabel;
};

#endif
