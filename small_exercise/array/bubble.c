#include <stdio.h>
#include <stdlib.h>
#define M 10

void bubble(int a[], int n);

int main(int argc, char *argv[])
{
	int i, j, temp, a[M];

	for (i = 0; i < M; i++)
		a[i] = rand() % 10;
	printf("before bubble:\n");
	for (i = 0; i < M; i++)
		printf("%2d", a[i]);
	bubble(a, M);
	printf("\nafter bubble:\n");
	for (i = 0; i < M; i++)
		printf("%2d", a[i]);
	printf("\n");

	return 0;
}

void bubble(int a[], int n)
{
	int i, j, temp;

	for (j = 0; j < n - 1; j++)
		for (i = n - 1; i > j; i--)
			if (a[i] > a[i - 1]) {
				temp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = temp;
			}
}
