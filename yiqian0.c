#include <stdio.h>

int main(void)
{
    int i,m=0,n=0,q=0,sum=0;
    for(i=1;i<=1000;i++)
    {if(0==i%5)
         {m++;
         if(0==i%25)
             {n++;
             if(0==i%125)
             q++;
             }
         }
     }
    sum=m+n+q;
    printf("0 is %d\n",sum);
    return 0;
}
