#include "qtcpcli.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyTcpCli myform;
    myform.setGeometry(0, 0, 300, 300);
    myform.show();

    return app.exec();
}
