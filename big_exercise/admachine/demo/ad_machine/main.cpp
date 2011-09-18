#include <QApplication>
#include <QTextCodec>
#include "mainForm.h"
#include <unistd.h>
#include <sys/file.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include "unix_socket.h"

#if 0

#define FB1_BPP			16
#define S3CFB_COLOR_KEY_START		_IO  ('F', 300)
#define S3CFB_COLOR_KEY_STOP		_IO  ('F', 301)
#define S3CFB_COLOR_KEY_SET_INFO	_IOW ('F', 304, s3cfb_color_key_info_t)
#define S3CFB_COLOR_KEY_VALUE		_IOW ('F', 305, s3cfb_color_val_info_t)


typedef struct {
	int direction;
	unsigned int compkey_red;
	unsigned int compkey_green;
	unsigned int compkey_blue;
} s3cfb_color_key_info_t;

typedef struct {
	unsigned int colval_red;
	unsigned int colval_green;
	unsigned int colval_blue;
} s3cfb_color_val_info_t;

int fb1_fd;

static void sig_del(int signo)
{

	ioctl(fb1_fd, SET_OSD_STOP);

	exit(0);

	return;
}
#endif

void *server_socket(void *a)
{
        int n;
        uid_t uid;
        int listenfd, connfd;
        char buf[4096];

        if((listenfd = serv_listen("/tmp/my_unix.socket")) < 0)
        {
                if(listenfd == -1)
                {
                        perror("socket error");
                        exit(1);
                }
                if(listenfd == -2)
                {
                        perror("bind error");
                        exit(1);
                }
                if(listenfd == -3)
                {
                        perror("listen error");
                        exit(1);
                }
        }

        while(1)
        {
conn_again:
                if((connfd = serv_accept(listenfd, &uid)) < 0)
                {
                        if(connfd == -1)
                        {
                                int errsv = errno;
                           /* EINTR为4，表示被信号中断，EAGAIN为11，
                                  表示设置了O_NONBLOCK同时没有连接被请
                                  求。两个宏定义在同一个文件
                                  asm-generic/errno-base.h中 */
                               if((errsv == EINTR) || (errsv == ECONNABORTED))
                                {
                                        printf("serv_accept again...\n");
                                        goto conn_again;
                                }
                                else
                                {
                                        printf("errno = %d,", errsv);
                                        errno = errsv;
                                        perror("accept error");
                                        exit(1);
                                }
                        }
                        else if(connfd == -2)
                        {
                                perror("stat error");
                                exit(1);
                        }
                        else if(connfd == -3)
                        {
                                perror("it's not a real socket file");
                                exit(1);
                        }
                }
                
                while(1)
                {
                        if((n = read(connfd, buf, 4096)) == -1)
                        {
                                perror("read connfd error");
                                exit(1);
                        }
                        else if(n == 0)
                        {
				//对端关闭
                                close(connfd);
                                break;
                        }
                        else
                        {
				               if(((strcmp(buf,"getpic") == 0) && (strlen(buf) == 6)) || ((strcmp(buf,"flush") == 0) && (strlen(buf) == 5 )))
				                {
                                    ((MainForm *)a)->pic->valchanged = 1;

                                }
                                if((strcmp(buf,"getpic") != 0))
                                    ((MainForm *)a)->message->setMsg(QString::fromUtf8(buf));
				
				memset(buf, 0, sizeof(buf));
                        }
                }
        }
}

int main(int argc, char *argv[])
{
#if 0
	//打开/dev/fb1层的osd显示
	s3c_win_info_t osd_info;
	s3cfb_color_key_info_t key_info;
	s3cfb_color_val_info_t key_val;


	// LCD frame buffer open
	fb1_fd = open(FB_DEV_NAME1, O_RDWR|O_NDELAY);
	if(fb1_fd < 0)
	{
		printf("LCD frame buffer open error\n");
		return -1;
	}

	if(signal(SIGINT, sig_del) == SIG_ERR) {
		printf("Sinal Error\n");
	}

	osd_info.Bpp		= FB1_BPP;	// RGB16
	osd_info.LeftTop_x	= 0;//400;	
	osd_info.LeftTop_y	= 0;//0;
	osd_info.Width		= 800;//FB1_WIDTH;	// display width
	osd_info.Height		= 480;//FB1_HEIGHT;	// display height

	// set OSD's information 
	if(ioctl(fb1_fd, SET_OSD_INFO, &osd_info)) {
		printf("Some problem with the ioctl SET_OSD_INFO\n");
		return -1;
	}
	ioctl(fb1_fd, SET_OSD_START);

	key_info.direction = 0;
	key_info.compkey_red = 0;
	key_info.compkey_green = 0;
	key_info.compkey_blue = 0;

	key_val.colval_red = 0;
	key_val.colval_green = 0;
	key_val.colval_blue = 0;

	ioctl(fb1_fd, S3CFB_COLOR_KEY_SET_INFO, &key_info);
	ioctl(fb1_fd, S3CFB_COLOR_KEY_VALUE, &key_val);

	ioctl(fb1_fd, S3CFB_COLOR_KEY_START);
#endif

	//以下是Qt程序
	const char filename[]  = "/tmp/mediaplayer";
	int fd = open (filename, O_CREAT|O_WRONLY, 0644);
	int lock =  lockf(fd,F_TLOCK,0);//file lock:cannot be execute than 1 time simultaneously
	if (fd == -1) {
		perror("open");
		exit(-1);
	}

	if (lock == -1) {
		perror("lock");
		exit(-1);
	}

    pthread_t ntid;
    
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    MainForm ad;
    ad.show();
    pthread_create(&ntid, NULL, server_socket, &ad);
    return app.exec();
}
