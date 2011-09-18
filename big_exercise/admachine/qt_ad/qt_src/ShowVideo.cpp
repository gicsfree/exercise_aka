#include "ShowVideo.h"

ShowVideo::ShowVideo(QWidget *parent)
  :QWidget(parent)
{
    myServerProcess = new QProcess(this);
    myMplayerProcess = new QProcess(this);
    myServerProcess->setStandardOutputProcess(myMplayerProcess);
    render = new QWidget(this);
    render->setGeometry(0, 0, 600, 500);

    //myServerProcess->start("../mplayer -zoom -x 400 -y 300 -playlist ../playlist.txt -loop 0 -slave");
    //myServerProcess->start("../mplayer -zoom -x 400 -y 300 -playlist ../playlist.txt -loop 0 -slave -wid id");

    //myServerProcess->setProcessChannelMode(QProcess::ForwardedChannels); //打印子进程显示的信息
    myServerProcess->start("../c_ser/cmd_ser/cmd_ser");
#if 1
    QStringList arg;
    arg << "-zoom";
    arg << "-x";
    arg << "400";
    arg << "-y";
    arg << "300";
    arg << "-playlist";
    arg << "../video/playlist.txt";
    arg << "-loop";
    arg << "0";
    arg << "-slave";
    arg << "-wid" << QString::number(render->winId());
    qDebug() << "arg: " << arg << endl;

    //myMplayerProcess->setProcessChannelMode(QProcess::ForwardedChannels); //打印子进程显示的信息
    myMplayerProcess->start("../mplayer/mplayer", arg);
#endif
}

ShowVideo::~ShowVideo()
{
    delete myServerProcess;
    delete myMplayerProcess;
    delete render;
}
