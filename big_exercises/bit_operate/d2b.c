#include <stdio.h>

void d2b()
{
	int i, j, binary,decimal;
    printf("input a decimal:");
    scanf("%d",&decimal);
	if ((decimal >> 31) & 1) {
		binary = ~(decimal - 1);
		printf("-");
	} else
		binary = decimal;
	for (i = 30; i >= 0; i--)
		if ((binary >> i) & 1)
			break;
	for (j = i; j >= 0; j--)
		printf("%d", ((binary >> j) & 1));
	printf("\n");

}
