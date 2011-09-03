#ifndef QTCP_H
#define QTCP_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>

class MyTcpServer: public QWidget
{
    Q_OBJECT

public:
    MyTcpServer(QWidget *parent = 0);
    ~MyTcpServer();

public slots:
    void accept(); //当客户端连接时，接受链接
    void process(); //当客户端发来数据时，处理数据

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QString data;
};

#endif
