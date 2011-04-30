#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i, n, y, r, sum = 0, flag = 0, a[12] =
	    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
	    b[12] = {
	0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	printf("input year:\n");
	scanf("%d", &n);
	if (n < 0) {
		printf("not legal\n");
		return 0;
	}
	printf("input month:\n");
	scanf("%d", &y);
	if (y < 0 || y > 12) {
		printf("not legal\n");
		return 0;
	}
	printf("input day:\n");
	scanf("%d", &r);
	if (r < 0 || r > 31) {
		printf("not legal\n");
		return 0;
	}
	if (n % 400 == 0)
		flag = 1;
	else if (n % 4 == 0 && n % 100 != 0)
		flag = 1;
	if (1 == flag)
		sum = a[y - 1] + r;
	else
		sum = b[y - 1] + r;
	printf("date is\n%d\n", sum);
	return 0;
}
