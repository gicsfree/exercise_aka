#include "qtcpcli.h"
#include <QDebug>
#include <QHostAddress>

MyTcpCli::MyTcpCli(QWidget *parent)
  :QWidget(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(process()));
    QHostAddress ser_addr("127.0.0.1");
    socket->connectToHost(ser_addr, 8000);

    lineedit = new QLineEdit(this);
    lineedit->clear();
    lineedit->setGeometry(0, 0, 200, 30);

    btn_send = new QPushButton("&Send", this);
    btn_send->setGeometry(0, 50, 100, 30);
    connect(btn_send, SIGNAL(clicked()), this, SLOT(sendmsg()));
}

MyTcpCli::~MyTcpCli()
{
    delete socket;
    delete lineedit;
    delete btn_send;
}

void MyTcpCli::process()
{
    while (socket->bytesAvailable() > 0)
    {
        data += socket->read(100);
    }
    qDebug() << "received msg: " << data << endl; 
    data = "";
}

void MyTcpCli::sendmsg()
{
    QString msg = lineedit->text();
    socket->write(msg.toUtf8());
    lineedit->clear();
}
