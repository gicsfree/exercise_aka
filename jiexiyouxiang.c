#include <stdio.h>
#include<stdlib.h>

void get_email(char *str);
int name(char s1);
int domain(char s2);

int main(int argc, const char *argv[])
{   FILE *fp;
    char string[1024];
    if(2!=argc)
        {printf("intput:./file1 file2\n");return 0;}
    if((fp=fopen(argv[1],"r"))==NULL)
    {printf("can't open file\n");
    exit(0);
    }
    while(fgets(string,1024,fp)!=NULL)
        get_email(string);
    fclose(fp);
    
    return 0;
}

void get_email(char *str)
{   char *p=str,*q,*r;
    while(*p)
        {if(*p=='@')
           {q=p-1;
           r=p+1;
           int m=0,n=0,i;
           while(name(*q)==1)
               {m++;q--;}
           while(domain(*r)==1)
               {n++;r++;}
                if((m>=1&&m<=32)&&(n>=1&&n<=64))
                  {for(i=0;i<m+n+1;i++)
                   printf("%c",*++q);
                   printf("\n");}
           } 
           p++;
        }
     
}
int name(char s1)
{if(s1>='a'&&s1<='z'||s1>='A'&&s1<'Z'||s1=='.'||s1=='_'||s1>='0'&&s1<='9')
    return 1;
    return 0;
}
int domain(char s2)
{if(s2>='a'&&s2<='z'||s2>='A'&&s2<='Z'||s2=='.'||s2=='-'||s2>='0'&&s2<='9')
    return 1;
    return 0;
}

