#include <stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    char ch;

    if(argc!=2)
        {printf("input : ./file1 file2\n");
        return 0;
        }

    if((fp=fopen(argv[1],"w"))==NULL)
    {printf("cannot open this file.\n");
    exit(1);
    }

    while((ch=getchar())!='\n')
        fputc(ch,fp);
    fclose(fp);
    
    return 0;
}
