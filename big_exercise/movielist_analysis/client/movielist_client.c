/* client_tcp.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "wrap.h"
#include "analysis.h"

#define DEFAULT_PORT_TCP 5050
#define DEFAULT_PORT_UDP 6000
#define RECV_BUF_LEN 128
#define LINE_LEN 1024
#define VERSION_LEN 20
#define VERSION "Version"
#define MOVIELIST "movielist.txt"

int tcp_download_list(char cli_addr[]);
int udp_get_vetsion(char cli_addr[]);
int get_version(char version[]);
int select_num(void);
void printf_func(void);
void empty_cache(void);

///////////////////////////////////////////////////////////////////
/*****************************************************************
* global variable: flag
* -1 : the movielist.txt is not exist !
*  0 : the vesion is the newest !
*  1 : the version is not the newest !
******************************************************************/
int flag = 0;

/*****************************************************************
* main
******************************************************************/
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: client[server IP address]\n");
        return -1;
    }
    while (1)
    {
        switch (select_num())
        {
            case 1:
                udp_get_version(argv[1]);
                if (1 == flag)
                    printf("the version is not the newest, you need download the newer !\n");
                else if (0 == flag)
                    printf("the version is the newest !\n");
                else
                    printf("the %s is not exist, you should download !\n", MOVIELIST);
                break;

        	case 2:
            	if (0 == tcp_download_list(argv[1]))
            	{
                	printf("download %s successfully !\n", MOVIELIST);
                	flag = 0;
            	}
            	break;

        	case 3:
            	udp_get_version(argv[1]);
            	if (-1 == flag)
                	printf("the %s is not exist, you should download !\n", MOVIELIST);
            	else if (0 == flag)
					printf("the version is the newest,you needn't update !\n");
            	else if (0 == tcp_download_list(argv[1]))
				{
					printf("update %s successfully !\n", MOVIELIST);
					flag = 0;
				}
				break;

        	case 4:
            	if (-1 == analysis())
					printf("the %s is not exist, you should download !\n", MOVIELIST);
            	break;

        	case 5:
            	return 0;

        }
    }

    return 0;

}

/***************************************************************
* get version from server ...
* return  -1 : the movielist.txt is not exist !
*          0 : the vesion is the newest !
*          1 : the version is not the newest !
****************************************************************/
int udp_get_version(char cli_addr[])
{
    int cPort = DEFAULT_PORT_UDP;
    int cClient = 0;
    unsigned int cLen = 0;
    int cSend = 0;
    int cRecv = 0;
    char send_buf[] = "Hello! I Am a Client!";
    char recv_buf[RECV_BUF_LEN];
    char version[VERSION_LEN];
    struct sockaddr_in cli;
   
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(cli_addr);
   
    cClient = Socket(AF_INET, SOCK_DGRAM, 0);
    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    cLen = sizeof(cli);

    cSend = Sendto(cClient, send_buf, sizeof(send_buf), 0, (struct sockaddr*)&cli, cLen);
    if (cSend < 0)
    {
        printf("sendto() failure!\n");
        return -1;
    }

    cRecv = Recvfrom(cClient, recv_buf, sizeof(version), 0, (struct sockaddr*)&cli, (unsigned int*)&cLen);
    if(cRecv < 0)
    {
        printf("recvfrom() failure!\n");
        return -1;
    }
	
    if (get_version(version) != 0)
    {
        flag = -1;
        return -1;
    }

    if (strncmp(version, recv_buf, sizeof(version)) != 0)
        flag = 1;

    close(cClient);

    return 0;
}

/*************************************************************
* download the movielist.txt from server
**************************************************************/
int tcp_download_list(char cli_addr[])
{
    
    int cPort = DEFAULT_PORT_TCP;
    int cClient = 0;
    int cRecv = 0;
    struct sockaddr_in cli;
    char recv_buf[RECV_BUF_LEN];
   
    memset(recv_buf, 0, sizeof(recv_buf));
   
    cli.sin_family = AF_INET;
    cli.sin_port = htons(cPort);
    cli.sin_addr.s_addr = inet_addr(cli_addr);
   
    cClient = Socket(AF_INET, SOCK_STREAM, 0);
    if(cClient < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    Connect(cClient, (struct sockaddr*)&cli, sizeof(cli)); 

    FILE *fp = fopen(MOVIELIST, "w+");
    if (fp == NULL)
    {
        printf("cannot open %s\n", MOVIELIST);
        return -1;
    }

    while (1)
    {   
        cRecv = Recv(cClient, recv_buf, sizeof(recv_buf), 0);   
        if(cRecv < 0)
        {
            printf("recv() failure!\n");
            return -1;
        } 
		else if (cRecv == 0)
		{
			fclose(fp);
			break;		
		}
		else
			fputs(recv_buf, fp);
    }
    
    Close(cClient);   

    return 0;
}

/**********************************************************
* get version from the client
* return -1 : the movielist.txt is not exist !
***********************************************************/
int get_version(char version[])
{
    FILE *fp;
    char aLine[LINE_LEN];

    fp = fopen(MOVIELIST, "r");
    if (fp == NULL)
    {
        printf("cannot open %s !\n", MOVIELIST);
        return -1;
    }
    while (fgets(aLine, LINE_LEN, fp) != NULL)
    {
        if (strstr(aLine, VERSION) != NULL)    
        {
            strncpy(version, aLine, VERSION_LEN);
            fclose(fp);
            break;
        }
    }

    return 0;
}

/**********************************************************
* select_num
***********************************************************/
int select_num(void)
{
    int num = 0;

    while (num < 1 || num > 5) {
        printf_func();
        if (0 == scanf("%d", &num)) 
            empty_cache();
    }

    return num;
}

/**********************************************************
* printf_func
***********************************************************/
void printf_func(void)
{
    printf("1.version test\n");
    printf("2.download list\n");
    printf("3.update list\n");
    printf("4.analysis list\n");
    printf("5.exit\n");
    printf("Please Select[1-5]:");
}

/**********************************************************
* empty_cache
***********************************************************/
void empty_cache(void)
{
    char ch;

    while ((ch = getchar()) != '\n');
}
























