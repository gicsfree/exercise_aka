#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i, j, k, n, m = 1, temp, b[5];
	printf("input int n:\n");
	scanf("%d", &n);
	if (n < 0)
		n = 0 - n;
	temp = n;
	for (; temp / 10 > 0; m++)
		temp /= 10;
	for (i = 0; i < m; i++) {
		b[i] = n % 10;
		n /= 10;
	}
	for (j = 0; j < m - 1; j++)
		for (k = j + 1; k < m; k++)
			if (b[k] == b[j]) {
				printf("yes\n");
				return 0;
			}
	printf("no\n");
	return 0;
}
