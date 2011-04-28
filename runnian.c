#include <stdio.h>
int runnian(int n);
int main(void)
{
    int n;
    printf("input n:\n");
    scanf("%d",&n);
    runnian(n);
    return 0;
}
int runnian(int n)
{   if(n<0)
    printf("wrong input\n");
    else
        if(0==n%400)
        printf("%d is runnian !\n",n);
        else
            if(0==n%4&&0!=n%100)
            printf("%d is runnian !\n",n);
            else
            printf("%d is not runnian !\n",n);
    return 0;
}
