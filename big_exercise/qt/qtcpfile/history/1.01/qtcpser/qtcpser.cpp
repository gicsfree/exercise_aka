#include "qtcpser.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDir>

MyTcpServer::MyTcpServer(QWidget *parent)
  :QWidget(parent), socket(NULL), file_size(0), ready(0), copyed_size(0)
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
    data = "";

    while (socket->bytesAvailable())
    {
        data += socket->read(4096);
    }

    //判断接收信息是否为":fileName:file_size:"
    if (data[0] == ':' && ready == 0)
    {
        QList<QByteArray> tmp = data.split(':');
        file_size = tmp[2].toInt();
        qDebug() << "fileName: " << tmp[1] << endl;
        qDebug() << "file_size: " << file_size << endl;
        QDir::setCurrent("/home/akaedu/Desktop/test");
        file.setFileName(tmp[1]);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << QString::fromUtf8("保存文件失败") << endl;
            goto err;
        }

        QByteArray msg = "OK";       
        socket->write(msg);
        ready = 1;

        return;
    }

    if (ready == 1)
    {
        //save to file
        file.write(data);

        //qDebug() << "recv: " << data << endl;
        copyed_size += data.length();
        if (copyed_size == file_size)
        {
            file.close();
            ready = 0;
            copyed_size = 0;
            qDebug() << QString::fromUtf8("拷贝完成") << endl;
            QByteArray msg = "finished";       
            socket->write(msg);
        }
    }

err:
    return;
}
