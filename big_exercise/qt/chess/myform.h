#ifndef MYFORM_H
#define MYFORM_H

#include <QtGui>
#include "stone.h"

class stone;

class myForm: public QWidget
{
public:
    myForm(QWidget *parent = 0);
    void paintEvent(QPaintEvent *); //窗体变化
    void mousePressEvent(QMouseEvent *event); //鼠标在窗体中点击
    int get_selectedid() const {return m_selectedid;} //私有成员不能被外界访问，使用此方法
    void set_selectedid(int id) {m_selectedid = id;}
    bool canMove(int cur_id, QPoint &to_pos); //myForm stone窗体位置对比，看是否能走

    stone *s[32]; //id做为下标去访问棋子,32个stone对象

private:
    int x_start;
    int y_start;
    int len;
    int m_selectedid; //被选中的棋子
};

#endif
