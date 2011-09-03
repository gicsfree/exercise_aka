#include "qtcpser.h"

MyTcpServer::MyTcpServer(QWidget *parent)
  :QWidget(parent), socket(NULL)
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8000);
    connect(server, SIGNAL(newConnection()), this, SLOT(accept()));
}

MyTcpServer::~MyTcpServer()
{
    delete server;
}

void MyTcpServer::accept()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(process()));
}

void MyTcpServer::process()
{
    while (socket->bytesAvailable())
    {
        QByteArray msg = socket->read(100);
        data = msg;
    }
    data = data.toUpper();
    socket->write(data.toUtf8());
}
