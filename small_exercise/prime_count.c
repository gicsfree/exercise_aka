#include <stdio.h>

int prime(int n);

int main(int argc, char *argv[])
{
	int n;
	printf("input n:\n");
	scanf("%d", &n);
	printf("prime is:\n");
	prime(n);
	return 0;
}

int prime(int n)
{
	int i, j, flag;
	for (i = 2; i <= n; i++) {
		flag = 1;
		for (j = 2; j < i; j++)
			if (0 == i % j) {
				flag = 0;
				break;
			}
		if (1 == flag)
			printf("%5d", i);
	}
	return 0;
}
