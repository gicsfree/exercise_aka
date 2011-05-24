/* server_tcp.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 5050
#define SUBF_LEN 128
#define FILENAME_LEN 20

int main(int argc, char** argv)
{
    int sPort = DEFAULT_PORT;
    int sListen = 0;
    int sAccept = 0;
    unsigned int sLen = 0;
    int sSend = 0,sRecv = 0;
    struct sockaddr_in ser;
    struct sockaddr_in cli;
    char sbuf[SUBF_LEN] ,filename[FILENAME_LEN];
    char is_exist[] = "is_exist";
    char no_exist[] = "no_exist";
    char finish[] = "finish";
   
    printf("Server waiting...\n");
   
    sListen = socket(AF_INET, SOCK_STREAM, 0);
    if(sListen < 0)
    {
        printf("socket() failure!\n");
        return -1;
    }
   
    ser.sin_family = AF_INET;
    ser.sin_port = htons(sPort);
    ser.sin_addr.s_addr = htonl(INADDR_ANY);
   
    if(bind(sListen, (struct sockaddr*)&ser, sizeof(ser)) < 0)
    {
        printf("bind() failure!\n");       
        return -1;
    }
   
    if(listen(sListen, 5) < 0)
    {
        printf("listen() failure!\n");        
        return -1;
    }

    while(1)
    {
	sLen = sizeof(cli);
    sAccept = accept(sListen, (struct sockaddr*)&cli, (unsigned int*)&sLen);
    if(sAccept < 0)
    {
        printf("accept() failure!\n");             
        break;
    }
   
    printf("accept() client IP: [%s]\n", (char*)inet_ntoa(cli.sin_addr));
    printf("accept() client PORT: [%d]\n", ntohs(cli.sin_port));
       
    sRecv=recv(sAccept, filename, sizeof(filename), 0);
    if(sRecv <= 0)
    {
        printf("recv(filename) failure!\n");
        return -1;
    }  

	FILE *fp = fopen(filename,"r");
    if (fp != NULL){
        sSend = send(sAccept, is_exist,sizeof(is_exist), 0);
        if(sSend <= 0)
        {
            printf("send(is_exist) failure!\n");
            return -1;
        } 

        while (fgets(sbuf, SUBF_LEN, fp) != NULL){        
            sSend = send(sAccept, sbuf, sizeof(sbuf), 0);
            if(sSend <= 0)
            {
                printf("send(text) failure!\n");
                return -1;
            } 
        }

    sSend = send(sAccept, finish,sizeof(finish), 0);
    if(sSend <= 0)
    {
        printf("send(finish) failure!\n");
        return -1;
    } 

    printf("download %s successfully !\n", filename);
	fclose(fp);
    } 
    else
    {
        printf("%s is not exist,download failed !\n", filename);
        sSend = send(sAccept, no_exist, sizeof(no_exist), 0);
        if(sSend <= 0)
        {
            printf("send(no_exist) failure!\n");
            return -1;
        } 
    }

    printf("Server waiting...\n");
    close(sAccept);
    }
    close(sListen);
   
    return 0;
}
