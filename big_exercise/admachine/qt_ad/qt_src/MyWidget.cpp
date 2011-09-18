#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent)
  :QWidget(parent)
{
    //bgLabel = new QLabel(this);
    //bgLabel->setPixmap(QPixmap("./images/mainform.png"));

    myShowVideo = new ShowVideo(this);

    myPicture = new MyPicture(this);

    myClock = new MyClock(this);

    myMessage = new MyMessage(this);
    myMessage->setMsg(tr("Hello World!")); 

    myDisplayPicture = new DisplayPicture(this); 

    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 6000);
    connect(server, SIGNAL(newConnection()), this, SLOT(accept())); 

    myProcess = new QProcess(this);
    myProcess->start("../c_ser/file_ser/file_ser");
}

void MyWidget::accept()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(process()));
}

void MyWidget::process()
{
    while (socket->bytesAvailable())
    {
        QByteArray msg = socket->read(100);
        data = msg;
    }

    //qDebug() << data << endl;  
    myMessage->setMsg(QString::fromUtf8(data.data()));   
}
