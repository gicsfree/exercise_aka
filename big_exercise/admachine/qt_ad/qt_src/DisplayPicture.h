#ifndef DISPLAYPICTURE_H
#define DISPLAYPICTURE_H

#include <QtGui>

class DisplayPicture: public QLabel
{
    Q_OBJECT

public:
    DisplayPicture(QWidget *parent = 0);
    void getPictureList();
    QPixmap *myPixmap[50];
    int isCountChanged;
    int cnt;
    int countPicture;

private slots:
    void displayPicture();

};

#endif // DISPLAYPICTURE_H
