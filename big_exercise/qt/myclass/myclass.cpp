#include <QApplication>

#include "myclass.h"
#include <iostream>
using namespace std;

myclass::myclass()
:m_cnt(0)
{
    
}

void myclass::do_print()
{
    cout << "printf something!" << endl;
    emit mysignal();
}

void myclass::do_mysignal()
{
//    static int m_cnt = 0;

    cout << "ceceive mysignal!" << endl;
    m_cnt++;
    if (m_cnt == 3)
    {
//        QApplication::quit();
        qApp->quit();
    }
}

void myclass::set_value(int newValue)
{
    emit int_mysignal(newValue);
    m_value = newValue;
}

int myclass::get_value()
{
    return m_value;
}

void myclass::int_myslot(int value)
{
    if (m_value != value)
    {
        cout << "not equal!" << endl;
    }
    else
    {
        cout << "equal!" << endl;
    }
}

