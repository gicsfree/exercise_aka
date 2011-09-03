#include "qtcpser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyTcpServer myform;
    //myform.show();

    return app.exec();
}
