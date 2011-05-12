#include <stdio.h>
int is_leap(int n);
int main(void)
{
	int n;
	printf("input year:\n");
	scanf("%d", &n);
	is_leap(n);
	return 0;
}

int is_leap(int n)
{
	if (n < 0)
		printf("wrong input\n");
	else if (0 == n % 400)
		printf("%d is leap year!\n", n);
	else if (0 == n % 4 && 0 != n % 100)
		printf("%d is leap year!\n", n);
	else
		printf("%d is not leap year!\n", n);
	return 0;
}
