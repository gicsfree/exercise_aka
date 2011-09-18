#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#include "unix_socket.h"
#include "wrap.h"

#define SERVER_PORT 9800
#define BUFSIZE 256
#define MAXLINE 80
#define NAMEMAXLEN 1024
#define MAXSIZE 1024

int send_no(int connfd){
	static char scces;
	scces = 'n';
	Write(connfd, &scces, 1);

	return 0;
}

void mywait(void)
{
	wait(NULL);     
}

int create_process(pid_t *pid)
{
	if(((*pid) = fork()) < 0)
	{
		perror("create process error");
		return -1;         
	}     

	if((*pid == 0)){
		execl("../MPlayer-1.0rc3/mplayer","./mplayer","-playlist",
		      "../MPlayer-1.0rc3/play.txt", "-slave","-loop","0", "&", NULL);
	}

	return 0;
}



int main(int argc, char **argv)
{

	char buf[BUFSIZE];
	int n,connfd;
	int server_sock,client_sock;
	socklen_t server_len,client_len;
	struct sockaddr_in server,client;

	char filename[MAXLINE];
	char new_filename[MAXLINE];
	char *pic_filename = "../ad_machine/picture/";
	char *video_filename = "../MPlayer-1.0rc3/";
	int  filelen;
	int fd, dl;
	char flag_n;
	int flag_trsf_movie = 0;
	int flag_trsf_pic = 0;
	char scces = 'y';

	pid_t pid = 0;

	struct sigaction myact;
	myact.sa_handler = mywait;
	myact.sa_flags = 0;
	sigaction(SIGCHLD,&myact,NULL);

	/*if(create_process(&pid) == -1)
	{
		exit(-1);                  
	}*/
     
	// 1. socket

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock < 0)
	{
		printf("create socket failed!\n");
		exit(1);
	}

	// 2. bind

	server_len = sizeof(server);
	bzero(&server, server_len);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(server_sock, (struct sockaddr *)&server, server_len) < 0)
	{
		printf("bind to port %d failed!\n", SERVER_PORT);
		exit(2);
	}

	// 3. listen

	if(listen(server_sock, 10) < 0)
	{
		printf("listen is failed!\n");
		exit(3);
	}

	// 4. accept

	while(1)
	{
		flag_trsf_movie = 0;
		flag_trsf_pic = 0;
		client_len = sizeof(client);
		client_sock = accept(server_sock, (struct sockaddr *)&client, &client_len);

		if(client_sock < 0)
		{
			printf("accept is failed!\n");
			close(server_sock);
			exit(4);
		}

		n = read(client_sock, &flag_n, 1);
		if(flag_n == '3')
		{
			strcpy(buf,"flush");
			buf[5] = '\0';
			goto ipc_conn;      
		}
		if(flag_n == '1')
		{
			bzero(buf,sizeof(buf));
			n = write(client_sock, &flag_n, 1);
			n = Read(client_sock, buf, BUFSIZE);
			close(client_sock);
		}
		else if(flag_n == '2')

		{
			for(;;){
				
				n = Write(client_sock, &flag_n, 1);

				Read(client_sock, filename, MAXLINE);
				printf("filename :%s\n",filename);
				
				if(strstr(filename, ".rmvb") || strstr(filename,".flv") || strstr(filename, ".mp4"))
				{
					strcpy(new_filename, video_filename);
					flag_trsf_movie = 1;
				}
				else if(strstr(filename, ".jpeg") || strstr(filename,".jpg") 
                                       || strstr(filename, ".bmp")|| strstr(filename, ".gif"))
				{
					strcpy(new_filename, pic_filename);
					flag_trsf_pic = 1;
				}
				strcat(new_filename, filename);

				if((fd = open(new_filename, O_CREAT | O_RDWR, S_IRWXU)) == -1){
					perror("file create");
					send_no(client_sock);
					break;
				}
				if((dl = open("../MPlayer-1.0rc3/play.txt", O_CREAT |O_TRUNC |O_RDWR, 777)) == -1){
					perror("create file error");
					return 0;
				}

				Write(dl, filename, strlen(filename));

				Write(client_sock, &scces, 1);

				Read(client_sock, &filelen, sizeof(filelen));


				if(filelen <= 0){
					send_no(client_sock);
					break;
				}
				scces = 'y';
				Write(client_sock, &scces, 1);
				n = ftruncate(fd,filelen);
				lseek(fd, 0, SEEK_SET);

				while((n = Read(client_sock, buf, BUFSIZE))){
					Write(fd, buf, n);
				}


				close(dl);
				break;
			}// end for(;;)
			close(client_sock);
			close(fd);
			
			if(flag_trsf_movie == 1){
				kill(pid, SIGKILL);
				if(create_process(&pid) == -1)
				{
					exit(-1);                        
				}

				continue;
			}//end if(flag_trsf_movie)
		}//end else if(flag_n == 2)

ipc_conn:
		/* as client for Qt*/
		if((connfd = cli_conn("/tmp/my_unix.socket")) < 0)
		{
			if(connfd == -1)
			{
				perror("socket error");
				exit(1);
			}
			else if(connfd == -2)
			{
				perror("bind error");
				exit(1);
			}
			else if(connfd == -4)
			{
				perror("connect error");
				exit(1);
			}
		}
		if(flag_trsf_pic == 1)
		{
			bzero(buf,sizeof(buf));
			strcpy(buf, "getpic");
			buf[6] = '\0'; 
		}

		n = write(connfd, buf, strlen(buf) + 1);

		//客户端关闭套接字，服务端read会返回0
		close(connfd);


	} //end while(1)
	return 0;  
}
