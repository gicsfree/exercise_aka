#include <stdio.h>
int decimal_to_binary(int n);

int main(int argc, char *argv[])
{
	int decimal;
	printf("input :decimal\n");
	scanf("%d", &decimal);
	decimal_to_binary(decimal);
	return 0;
}

int decimal_to_binary(int n)
{
	int i, j, binary;
	if ((n >> 31) & 1) {
		binary = ~(n - 1);
		printf("-");
	} else
		binary = n;
	for (i = 30; i >= 0; i--)
		if ((binary >> i) & 1)
			break;
	for (j = i; j >= 0; j--)
		printf("%d", ((binary >> j) & 1));
	printf("\n");

	return 0;
}
