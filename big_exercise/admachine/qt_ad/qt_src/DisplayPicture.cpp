#include "DisplayPicture.h"

DisplayPicture::DisplayPicture(QWidget *parent)
  :QLabel(parent)
{    
    cnt = 0;
    countPicture = 0;
    isCountChanged = 0;

    setGeometry(600, 100, 200, 400);

    getPictureList(); 
    displayPicture();

    QTimer *timer = new QTimer(parent);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(displayPicture()));
    timer->start(2000);
}

void DisplayPicture::getPictureList()
{        
    QDir *dir = new QDir("../picture");

    QStringList filters;
    filters << "*.jpg" << "*.bmp" << "*.jpeg";

    QStringList *stringList = new QStringList();
    *stringList = dir->entryList(filters);    
    countPicture = stringList->count();

    for (int i = 0; i < countPicture; i++)
    {
        myPixmap[i] = new QPixmap("../picture/" + stringList->at(i));
    }
                
    delete dir;
    delete stringList;
}

void DisplayPicture::displayPicture()
{    
    setPixmap(myPixmap[cnt]->scaled(width(), height()));

    cnt++;
    if (cnt >= countPicture)
    {
        cnt = 0;
    }

    if (isCountChanged == 1)
    {
        getPictureList();
        isCountChanged = 0;
    }
}
