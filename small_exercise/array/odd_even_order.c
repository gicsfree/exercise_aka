#include <stdio.h>

int main(int argc,char *argv[])
{
	int i, j = 0, k = 19, m, n, temp, b[20], a[20] =
	    { 12, 1, 48, 67, 78, 15, 58, 36, 24, 15, 38, 64, 59, 67, 65,
		58, 69, 34, 27, 61
	};
	printf("before sort:\n");
	for (i = 0; i < 20; i++) {
		printf("%3d", a[i]);
		if (a[i] % 2 == 1)
			b[j++] = a[i];
		else
			b[k--] = a[i];
	}
	for (m = 0; m < j - 1; m++)
		for (n = m + 1; n < j; n++)
			if (b[m] > b[n]) {
				temp = b[m];
				b[m] = b[n];
				b[n] = temp;
			}
	for (m = k + 1; m < 19; m++)
		for (n = m + 1; n < 20; n++)
			if (b[m] > b[n]) {
				temp = b[m];
				b[m] = b[n];
				b[n] = temp;
			}

	printf("\nafter sort:\n");
	for (i = 0; i < 20; i++)
		printf("%3d", b[i]);
	return 0;
}
