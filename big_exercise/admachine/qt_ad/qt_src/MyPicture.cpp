#include "MyPicture.h"

MyPicture::MyPicture(QWidget *parent)
  :QLabel(parent)
{    
    setGeometry(600, 0, 200, 400);
    QPixmap *myPixmap = new QPixmap("./images/tomandjerry.jpg");
    setPixmap(myPixmap->scaled(width(), height()));
}
