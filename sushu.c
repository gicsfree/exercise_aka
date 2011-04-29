#include <stdio.h>

int main(int argc, const char *argv[])
{
    int n;
    printf("input n:\n");
    scanf("%d",&n);
    printf("sushu is:\n");
    sushu(n);
    return 0;
}

int sushu(int n)
{
    int i,j,flag;
    for(i=2;i<=n;i++)
    {flag=1;
    for(j=2;j<i;j++)
        if(0==i%j)
        {flag=0;break;}
    if(1==flag)
        printf("%5d",i);
    }
    return 0;
}
