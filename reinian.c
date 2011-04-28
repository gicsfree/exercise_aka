#include <stdio.h>
int reinian(int n);
int main(void)
{
    int n;
    printf("input n:\n");
    scanf("%d",&n);
    reinian(n);
    return 0;
}
int reinian(int n)
{   if(n<0)
    printf("wrong input\n");
    else
        if(0==n%400)
        printf("%d is reinian !\n",n);
        else
            if(0==n%4&&0!=n%100)
            printf("%d is reinian !\n",n);
            else
            printf("%d is not reinian !\n",n);
    return 0;
}
