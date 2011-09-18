#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cgi.h"

#define MAXLINE 80
#define BUFSIZE 80
#define SERV_PORT 9800
#define MAXSIZE 1024
int main(int argc, char *argv[])
{
	cgi_init();
	cgi_process_form();
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXSIZE];

	int sockfd, n;
	char flush[BUFSIZE];
	char str[BUFSIZE];
	char local_dir[BUFSIZE] = "/home/xwp/upload/";

	int fd;
	char flag_n;
	struct stat f_stat;

	char filename[BUFSIZE];
	char scces = 'n';

	bzero(flush, sizeof(flush));
	bzero(str, sizeof(str));
	bzero(filename, sizeof(filename));
	if(cgi_param("msg")){
		strcpy(str,cgi_param("msg"));}
	if(cgi_param("video")){
		strcpy(filename,cgi_param("video"));}
	if(cgi_param("Flush")){
		strcpy(flush,cgi_param("Flush"));}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliaddr.sin_port = htons(SERV_PORT + 1);

	bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)); 
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(strlen(str) != 0)
	{
		flag_n = '1';
		write(sockfd, &flag_n, sizeof(flag_n));
		read(sockfd, &flag_n, sizeof(flag_n));
		if((n = write(sockfd, str, strlen(str))) > 0)
		{
			cgi_redirect("../word.html");
			cgi_end();
			close(sockfd);	
			return 0;
		}
	}
	else if(strlen(filename) != 0)
	{
		{  
			flag_n = '2';
			write(sockfd, &flag_n, sizeof(flag_n));
			read(sockfd, &flag_n, sizeof(flag_n));
			strcat(local_dir, filename);

			write(sockfd, filename, strlen(filename) + 1);
			read(sockfd, &scces, 1);

			if(scces != 'y'){

			}

			if(stat(local_dir,&f_stat) == -1){

			}

			write(sockfd, &f_stat.st_size, sizeof(f_stat.st_size));
			read(sockfd, &scces, 1);

			if(scces != 'y'){

			}

			if((fd = open(local_dir, O_RDONLY)) == -1){

			}

			while((n = read(fd, buf, MAXSIZE))){
				write(sockfd, buf, n);
			}
			cgi_redirect("../upload.html");
		}
		close(fd);
		cgi_end();
		close(sockfd);	
		return 0;
	}
	else if(strlen(flush) != 0)
	{
		flag_n = '0';
		write(sockfd, &flag_n, sizeof(flag_n));
		//read(sockfd, &flag_n, sizeof(flag_n));
		//if((n = write(sockfd, flush, strlen(flush))) > 0)
		//{
			cgi_redirect("../flash.html");
			cgi_end();
			close(sockfd);	
			return 0;
		//}
	}

}
