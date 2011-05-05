#include <stdio.h>
int ywcf(int m,int n);

int main(int argc,char *argv[])
{
    int m,n;
    printf("input :m n\n");
    scanf("%d %d",&m,&n);
    printf("%d\n",ywcf(m,n));
    return 0;
}

int ywcf(int m,int n)
{
    int i,p,q,result=0,flag=0;
    if((m >> 31) & 1)
        p=~(m-1);
    else
        p=m;
    if((n >> 31) & 1)
        q=~(n-1);
    else
        q=n;
    if(((m >> 31) & 1) ^ ((n >> 31) & 1))
        flag=1;
    for(i=0;i<31;i++)
        if((p >> i) & 1)
            result+=q << i;
    if(1==flag)
        result=~result + 1;

    return result;
}


