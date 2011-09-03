#ifndef MYFORM_H
#define MYFORM_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>
#include "ui_form.h"

class myForm: public QWidget, public Ui_Form
{
    Q_OBJECT

public:
    myForm(QWidget *parent = 0);
    ~myForm();

public slots:
    void process();
    void connect_to_ser();
    void send_file();
    void connect_ok();
    void connect_err(QAbstractSocket::SocketError socketError);
    void do_timer();

private:
    QTcpSocket *socket;
    QTimer *timer;
    int socket_state;
    int file_size;
    int copyed_size;
    QString fileName;
    QString buf; //存放接收到的信息
};

#endif
