#include <stdio.h>
#include<stdlib.h>

void joseph(int m, int n)
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
