#include <QApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList leader;
    leader << "hello1" << "hello2" << "hello3" << "hello4";
    
    QFile file("test.txt");
    if (!file.open(QIODevice::ReadWrite))
    {
        cerr << "Cannot open file for writing:" << qPrintable(file.errorString()) << endl;
        return -1;
    }

    //write file
    QTextStream out(&file);
    for (int i = 0; i < leader.count(); i++)
    {
        out<<leader[i] << endl; 
    }

    //read file
    QTextStream in(&file);
    QStringList strlist;
    QString tmp;
    //file.seek(0);
    file.close();
    if (!file.open(QIODevice::ReadWrite))
    {
        cerr << "Cannot open file for writing:" << qPrintable(file.errorString()) << endl;
        return -1;
    }
    
    while ((tmp = in.readLine()).compare("") != 0)
    {
        qDebug() << "tmp: " << tmp << endl;
        strlist << tmp;
    }
    qDebug() << "strlist: " << strlist << endl;

    file.close();

    return 0;
}
