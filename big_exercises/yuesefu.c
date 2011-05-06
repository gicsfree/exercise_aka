#include <stdio.h>
#include<stdlib.h>
void yuesefu(int m, int n);

int main(int argc,char *argv[])
{
	int i, m, n;
	if (3 != argc) {
		printf("input(m<n): ./file m(1-100) n(1-100)\n");
		return 0;
	}
	for (i = 1; i <= 2; i++)
		if (atoi(argv[i]) < 1 || atoi(argv[i]) > 100) {
			printf("input(m<n): ./file m(1-100) n(1-100)\n");
			return 0;
		}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	if (m > n) {
		printf("input(m<n): ./file m(1-100) n(1-100)\n");
		return 0;
	}
	yuesefu(m, n);
	return 0;
}

void yuesefu(int m, int n)
{
	int i, j = 0, k = 0, q = 0, a[101];
	for (i = 0; i < 101; i++)
		a[i] = 1;
	while (k < n) {
		for (i = 1; i <= n; i++)
			if (1 == a[i]) {
				j++;
				if (j == m) {
					j = 0;
					a[i] = 0;
					k++;
					{
						q++;
						printf("%3d:%3d out.",k,
						       i);
						if (q % 5 == 0)
							printf("\n");
					}
				}
			}
	}
}
