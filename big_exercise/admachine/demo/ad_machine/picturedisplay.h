#ifndef PICTUREDISPLAY_H
#define PICTUREDISPLAY_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QPixmap>

class myPicture:public QLabel
{
Q_OBJECT
public:
    myPicture(QWidget *parent);
    void file_list();
    //void addpic(QString *name);
    QPixmap *picmap[50];
    int valchanged;
    int k;
    int listlen;
private slots:
    void show_picture();

private:
    QString str;
    QLabel *label_pic_dis;
};

#endif // PICTUREDISPLAY_H
