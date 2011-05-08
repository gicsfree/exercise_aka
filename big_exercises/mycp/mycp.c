#include <stdio.h>
#include <stdlib.h>

int mycp(const char *src,const char *dest,int choice);
static int cp_by_char(FILE *src,FILE *dest);
static int cp_by_record(FILE *src,FILE *dest);
static int cp_by_row(FILE *src,FILE *dest);

int mycp(const char *src,const char *dest,int choice)
{
    FILE *fp1,*fp2;
    if ((fp1=fopen(src,"r"))==NULL){
        printf("can't open:%s\n",src);
        exit(1);
        }
    if ((fp2=fopen(dest,"w"))==NULL){
        printf("can't open:%s\n",dest);
        exit(1);
        }

    switch(choice){
    case 1:cp_by_char(fp1,fp2);break;
    case 2:cp_by_record(fp1,fp2);break;
    case 3:cp_by_row(fp1,fp2);break;
    }
   
   fclose(fp1);
   fclose(fp2);
   return 0;
}

static int cp_by_char(FILE *src,FILE *dest)
{
    char ch;
    while((ch=fgetc(src))!=EOF)
        fputc(ch,dest);
    
    return 0;
}

static int cp_by_record(FILE *src,FILE *dest)
{
    char buff[128];
    while(fread(buff,1,1,src)!=0)
        fwrite(buff,1,1,dest);
    
    return 0;
}

static int cp_by_row(FILE *src,FILE *dest)
{
    char string[81];
    while(fgets(string,81,src)!=NULL)
        fputs(string,dest);
    
    return 0;
}
