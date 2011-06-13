/* bubble.c */

#include <stdio.h>
#include <assert.h>

#define N 5

/* sort */
void sort(int arr[], int n)
{
	assert(arr != NULL);
	assert(n > 0);

	int i;
	int j;
	int temp;

	for (i = 1; i < n; i++) {
		for (j = n - 1; j >= i; j--) {
			if (arr[j] > arr[j - 1]) {
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}

/* main */
int main(int argc, const char *argv[])
{
	int i;
	int array[N] = { 1, 2, 5, 4, 3 };

	printf("array:");
	for (i = 0; i < N; i++)
		printf("%3d", array[i]);
	sort(array, N);
	printf("\nafter sort:");
	for (i = 0; i < N; i++)
		printf("%3d", array[i]);
	printf("\n");

	return 0;
}
