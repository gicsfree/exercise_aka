#include <stdio.h>
int dcb(int n);

int main(int argc, char *argv[])
{
	int m;
	printf("input :m\n");
	scanf("%d", &m);
	dcb(m);
	return 0;
}

int dcb(int n)
{
	int i, j, p;
	if ((n >> 31) & 1) {
		p = ~(n - 1);
		printf("-");
	} else
		p = n;
	for (i = 30; i >= 0; i--)
		if ((p >> i) & 1)
			break;
	for (j = i; j >= 0; j--)
		printf("%d", ((p >> j) & 1));
	printf("\n");

	return 0;
}
