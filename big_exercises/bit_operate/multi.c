#include <stdio.h>

void multi()
{
	int i, p, q,m,n, result = 0, flag = 0;
    printf("input x y:");
    scanf("%d %d",&m,&n);
	if ((m >> 31) & 1)
		p = ~(m - 1);
	else
		p = m;
	if ((n >> 31) & 1)
		q = ~(n - 1);
	else
		q = n;
	if (((m >> 31) & 1) ^ ((n >> 31) & 1))
		flag = 1;
	for (i = 0; i < 31; i++)
		if ((p >> i) & 1)
			result += q << i;
	if (1 == flag)
		result = ~result + 1;
    printf("x * y=%d\n",result);

}
