#include "qtcpcli.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QtTest>

MyTcpCli::MyTcpCli(QWidget *parent)
  :QWidget(parent), socket_state(0), copyed_size(0)
{
    setupUi(this);

    socket = new QTcpSocket(this);

    connect(btn_connect, SIGNAL(clicked()), this, SLOT(connect_to_ser()));
    connect(socket, SIGNAL(connected()), this, SLOT(connect_ok()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connect_err(QAbstractSocket::SocketError)));
    connect(btn_send, SIGNAL(clicked()), this, SLOT(send_file()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(process()));
    
    ledt_ip->setText("127.0.0.1");

    progressBar->setRange(0, 100); //百分比
    progressBar->setValue(0);

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(do_timer()));
}

MyTcpCli::~MyTcpCli()
{
    delete socket;
}

void MyTcpCli::do_timer()
{
    progressBar->setValue(copyed_size);
}

void MyTcpCli::connect_to_ser()
{
    QHostAddress ser_addr(ledt_ip->text());
    socket->connectToHost(ser_addr, 8000);
}

void MyTcpCli::connect_ok()
{
    socket_state = 1;
    QMessageBox msgbox;
    msgbox.setText(tr("连接成功"));
    msgbox.exec();   
}

void MyTcpCli::connect_err(QAbstractSocket::SocketError socketError)
{
    socket_state = 0;
    qDebug() << "socketError: " << socketError << endl;
    QMessageBox msgbox;
    msgbox.setText(tr("连接失败"));
    msgbox.exec();
}

void MyTcpCli::send_file()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home");
    ledt_file->setText(fileName);
    qDebug() << "open file name: " << fileName << endl;

    //get file size
    QFile file(fileName);
    if (file.exists())
    {
        file_size = file.size();
        progressBar->setRange(0, file_size); //设置进度条范围
        qDebug() << "file size: " << file_size << endl;
    }    
    else
    {
        QMessageBox msgbox;
        msgbox.setText(tr("The file is not exist"));
        msgbox.exec();
    }

    //send ":fileName:file_size:"
    if (socket_state == 1)
    {
        QByteArray msg = ":";
        QFileInfo fi(fileName); 
        msg += fi.fileName();
        msg += ":";
        msg += QString::number(file_size);
        msg += ":";
        qDebug() << ":fileName:file_size:" << msg << endl;
        socket->write(msg);
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("网络套接字未连接"));
    }
}

void MyTcpCli::process()
{
    buf = "";
    while (socket->bytesAvailable() > 0)
    {
        buf += socket->readAll();
    }

    qDebug() << "recv buf: " << buf << endl;

    if (buf.compare("OK") == 0)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox msgbox;
            msgbox.setText(tr("打开文件失败"));
            msgbox.exec();
            goto err;
        }

        //timer->start();

        //发送文件
        while (!file.atEnd())
        {
            QByteArray tmp = file.read(4096);
            //qDebug() << "send: " << tmp << endl;
            socket->write(tmp);
            copyed_size += tmp.length();
            //qDebug() << "copyed_size: " << copyed_size << endl;
            //qDebug() << "tmp.length: " << tmp.length() << endl;
            progressBar->setValue(copyed_size);
            //QTest::qWait(1);
        }
    
        file.close();
    }
    else if (buf.compare("Finished") == 0)
    {
        copyed_size = 0;
        QMessageBox msgbox;
        msgbox.setText(tr("发送完成"));
        msgbox.exec();
        progressBar->setValue(0);
    }
    else if (buf.compare("ERR") == 0)
    {
        QMessageBox msgbox;
        msgbox.setText(tr("发送失败"));
        msgbox.exec(); 
        goto err;       
    }
    else //some error
    {
        qDebug() << "some error!" << endl;
        goto err;
    }

    //send ok

err:
    return;
}
