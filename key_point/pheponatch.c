/* pheponatch.c */

#include <stdio.h>

#define N 10

/* pheponatch */
int pheponatch(int n)
{
	if (n < 1)
		return -1;
	else if ((n == 1) || (n == 2))
		return 1;
	else
		return (pheponatch(n - 1) + pheponatch(n - 2));
}

/* main */
int main(int argc, const char *argv[])
{
	int ret = pheponatch(N);

	if (ret != -1)
		printf("the %dth of pheponatch is: %d\n", N, ret);
	else
		printf("N must be larger than 0 !\n");

	return 0;
}
