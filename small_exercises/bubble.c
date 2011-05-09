#include <stdio.h>

int main(int argc, char *argv[])
{
	int temp, i, j, a[10] = { 5, 6, 32, 1, 87, 23, 234, 3, 7, 123 };
	printf("before bubble:\n");
	for (i = 0; i < 10; i++)
		printf("%4d", a[i]);
	for (j = 0; j < 9; j++)
		for (i = 9; i > j; i--)
			if (a[i] > a[i - 1]) {
				temp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = temp;
			}
	printf("\nafter bubble:\n");
	for (i = 0; i < 10; i++)
		printf("%4d", a[i]);
	return 0;
}
