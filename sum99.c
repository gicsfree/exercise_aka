#include <stdio.h>

int main(void)
{
    int n,sum=0;
    for(n=1;n<99;n+=2)
    sum+=n;
    printf("sum is %d\n",sum);
    return 0;
}
