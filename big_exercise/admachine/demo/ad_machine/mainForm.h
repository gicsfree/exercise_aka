#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include "message.h"
#include "picturedisplay.h"
class MainForm:public QDialog
{
public:
    MainForm(QWidget *parent = 0);
    void myForm();
    MyMessage *message;
    myPicture *pic;
private:
    QString filename;

};

#endif // MAINFORM_H
