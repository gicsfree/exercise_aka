#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i, j, k = 0, n, b[5];
	printf("input int n:\n");
	scanf("%d", &n);
	if (n < 0)
		n = 0 - n;
	while (n) {
		b[k++] = n % 10;
		n /= 10;
	}
	for (i = 0; i < k - 1; i++)
		for (j = i + 1; j < k; j++)
			if (b[i] == b[j]) {
				printf("yes\n");
				return 0;
			}
	printf("no\n");
	return 0;
}
