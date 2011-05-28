/* server_tcp.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "wrap.h"

#define DEFAULT_PORT_TCP 5050
#define DEFAULT_PORT_UDP 6000
#define SEND_BUF_LEN 128
#define RECV_BUF_LEN 128
#define VERSION_LEN 20 
#define LINE_LEN 1024
#define VERSION "Version"
#define MOVIELIST "movielist.txt"

void get_version(char version[]);


void * udp_send_version(void *sPara)
{
    int sPort = DEFAULT_PORT_UDP;
    int sSocket = 0;
    int sLen = 0;
    int sSend = 0;
    int sRecv = 0;
    char send_buf[SEND_BUF_LEN];
    char recv_buf[RECV_BUF_LEN];
    char version[VERSION_LEN];
    struct sockaddr_in ser;
    struct sockaddr_in cli;
   
    sSocket = Socket(AF_INET, SOCK_DGRAM, 0);
    if(sSocket < 0)
    {
        printf("socket() failure!\n");
        return NULL;
    }
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(sPort);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
   
    Bind(sSocket, (struct sockaddr*)&ser, sizeof(ser));
   
    while(1)
    {
        sLen = sizeof(cli);
        sRecv = Recvfrom(sSocket, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&cli, (unsigned int*)&sLen);
        if(sRecv < 0)
        {
            printf("recvfrom() failure!\n");
            break;
        }
        else
        {
            printf("recvfrom(): [%s]\n", recv_buf);
            printf("recvfrom() client IP: [%s]\n", inet_ntoa(cli.sin_addr));
            printf("recvfrom() client PORT: [%d]\n", ntohs(cli.sin_port));
        }

        get_version(version);       
        sSend = Sendto(sSocket, version, sizeof(version), 0, (struct sockaddr*)&cli, sizeof(cli));
        if (sSend < 0)
        {
            printf("sendto() failure!\n");
            return NULL;
        }
        printf("sendto() succeeded.\n");
        printf("Server waiting...\n");
        sleep(3);
    }
    Close(sSocket);
   
}

int main(int argc, char** argv)
{
    int sPort = DEFAULT_PORT_TCP;
    int sListen = 0;
    int sAccept = 0;
    unsigned int sLen = 0;
    struct sockaddr_in ser;
    struct sockaddr_in cli;
    int sSend = 0,sRecv = 0;
    char send_buf[SEND_BUF_LEN];
    char is_exist[] = "is_exist";
    char no_exist[] = "no_exist";
    char update[10] = "update";
    char finish[] = "finish";
    char is_update[10];

    pthread_t thread;
    pthread_create(&thread, NULL, udp_send_version, NULL);

    printf("Server waiting...\n");
   
    sListen = Socket(AF_INET, SOCK_STREAM, 0);
    if(sListen < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(sPort);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
   
    Bind(sListen, (struct sockaddr*)&ser, sizeof(ser));
   
    Listen(sListen, 5); 

    while(1)
    {
        sLen = sizeof(cli);
        sAccept = Accept(sListen, (struct sockaddr*)&cli, (unsigned int*)&sLen);
        if(sAccept < 0)
        {
            printf("accept() failure!\n");             
            break;
        }
   
        printf("accept() client IP: [%s]\n", (char*)inet_ntoa(cli.sin_addr));
        printf("accept() client PORT: [%d]\n", ntohs(cli.sin_port));  

        FILE *fp = fopen(MOVIELIST,"r");
        if (fp == NULL)
        {
            printf("cannot open %s\n", MOVIELIST);
            return -1;
        }

        while (fgets(send_buf, SEND_BUF_LEN, fp) != NULL)
        {        
            sSend = Send(sAccept, send_buf, sizeof(send_buf), 0);
            if(sSend < 0)
            {
                printf("send(txt) failure!\n");
                return -1;
            } 
        }
        fclose(fp);

        sSend = Send(sAccept, finish, sizeof(finish), 0);
        if(sSend < 0)
        {
            printf("send(finish) failure!\n");
            return -1;
        } 

        printf("download %s successfully !\n", MOVIELIST);

        printf("Server waiting...\n");
        Close(sAccept);
        sleep(2);
    }
    Close(sListen);
   
    return 0;
}

void get_version(char version[])
{
    FILE *fp;
    char aLine[LINE_LEN];

    fp = fopen(MOVIELIST, "r");
    if (fp == NULL)
    {
        printf("cannot open %s !\n", MOVIELIST);
        exit(1);
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
}


