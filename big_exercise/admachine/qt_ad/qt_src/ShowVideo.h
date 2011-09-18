#ifndef SHOWVIDEO_H
#define SHOWVIDEO_H

#include <QtGui>

class ShowVideo: public QWidget
{
public:
    ShowVideo(QWidget *parent = 0);
    ~ShowVideo();

private:
    QProcess *myServerProcess; //send "p\n"
    QProcess *myMplayerProcess; //read output of myServerProcess, so it will runs "mplayer"
    QWidget *render; //用来显示视频的子窗体
};

#endif
