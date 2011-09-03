#ifndef QTCPCLI_H
#define QTCPCLI_H

#include <QTcpSocket>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class MyTcpCli: public QWidget
{
    Q_OBJECT

public:
    MyTcpCli(QWidget *parent = 0);
    ~MyTcpCli();

public slots:
    void process();
    void sendmsg();

private:
    QTcpSocket *socket;
    QLineEdit *lineedit;
    QPushButton *btn_send;
    QString data;
};

#endif
