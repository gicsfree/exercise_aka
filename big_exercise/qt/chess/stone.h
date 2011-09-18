#ifndef STONE_H
#define STONE_H

#include "myform.h"
#include <QtGui>

class myForm;

class stone: public QWidget
{
    Q_OBJECT

public:
    typedef enum s_color {BLACK, RED} scolor_t;
    stone(int id, int type, scolor_t red, QWidget *parent = 0);

    void paintEvent(QPaintEvent *); //窗体变化
    void mousePressEvent(QMouseEvent *); //鼠标在窗体中点击
    int get_type() const {return m_type;} //myForm类不能直接访问stone类的私有成员，使用成员函数得到
    static myForm *palate; //静态指针每个stone对象都能访问myForm类
    QPoint stone_pos; //棋子在棋盘中对应的位置

private:
    int m_id; //id = 0~31, 红0-15， 黑16-31
    int m_type; //0车，1马，2象，3士，4帅，5炮，6卒
    scolor_t m_red; //1red, 0black
    bool m_killed; //true killed, default is false
    int m_selected; //是不是正在点击或选中的棋子 1表示选中的
};

#endif
