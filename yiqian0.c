#include <stdio.h>
int ling(int n);

int main(void)
{
	int i,n,sum;
    printf("input n:\n");
    scanf("%d",&n);
    sum=ling(n);
	printf("0 is %d\n", sum);
	return 0;
}
int ling(int n)
{int i,sum=0;
for(i=5;n/i>=1;i*=5)
sum+=n/i;
return sum;
}
