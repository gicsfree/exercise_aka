#include <QApplication>
#include <QPushButton>
#include <QWidget>

#include "myclass.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget myform;
    myform.show();

    QPushButton hello("Hello world!", &myform);
    hello.resize(200, 100);
    hello.show();

    myclass a;
//    a.do_print();
//    QObject::connect(&hello, SIGNAL(clicked()), &a, SLOT(do_print()));
    QObject::connect(&hello, SIGNAL(clicked()), &a, SIGNAL(mysignal()));
    QObject::connect(&a, SIGNAL(mysignal()), &a, SLOT(do_mysignal()));
    QObject::connect(&a, SIGNAL(int_mysignal(int)), &a, SLOT(int_myslot(int)));
    a.set_value(1);
    a.set_value(2);
    a.set_value(2);

    return app.exec();
}
