/* count_1.c */
#include <stdio.h>

#define N 9999			// 0010,0111,0000,1111

/* count 1 in x */
int func(int x)
{
	if (x == 0)
		return 0;

	if (x < 0)
		x = -x;

	int count1 = 0;

	while (x > 0) {
		count1++;
		x = x & (x - 1);
	}

	return count1;
}

/* main */
int main(int argc, const char *argv[])
{
	printf("%d have %d (1)\n", N, func(N));

	return 0;
}
