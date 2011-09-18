#ifndef MYFORM_H
#define MYFORM_H

#include <QtGui>

class myForm: public QWidget
{
public:
    myForm(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif
