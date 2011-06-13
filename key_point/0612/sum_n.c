/* sum_n.c */

#include <stdio.h>
#include <assert.h>

#define N 100

/* sum 1 to n */
long sum_n(int n)
{
	assert(n > 0);

	return (long) (n * (n + 1) / 2);
}

/* main */
int main(int argc, const char *argv[])
{
	printf("sum 1 to %d is: %ld\n", N, sum_n(N));

	return 0;
}
