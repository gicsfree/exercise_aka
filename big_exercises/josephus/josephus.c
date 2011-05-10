#include <stdio.h>
#include<stdlib.h>

void josephus(int m, int n)
{
	int i, cnt = 0, out = 0, q = 0, a[101];
	for (i = 0; i < 101; i++)
		a[i] = 1;
	while (out < n) {
		for (i = 1; i <= n; i++)
			if (1 == a[i]) {
				cnt++;
				if (cnt == m) {
					cnt = 0;
					a[i] = 0;
					out++;
					{
						q++;
						printf("%3d:%3d out.", out,
						       i);
						if (q % 5 == 0)
							printf("\n");
					}
				}
			}
	}
}
