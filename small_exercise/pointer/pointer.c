#include <stdio.h>
void swap(int *x, int *y);
void p_swap(int *x, int *y);

int main(int argc, char *argv[])
{
	int a[10] = { 0 }, x = 3, y = 4;
	int (*pa)[10] = &a;

	pa++;
	printf("%p\n", &a);
	printf("%p\n", pa);
	printf("%d\n", pa - &a);
	printf("%d\n", sizeof(pa - &a));

	printf("x=%d,y=%d\n", x, y);
	swap(&x, &y);
	printf("x=%d,y=%d\n", x, y);

	printf("&x=%p,&y=%p\n", &x, &y);
	p_swap(&x, &y);
	printf("&x=%p,&y=%p\n", &x, &y);

	return 0;
}

void swap(int *x, int *y)
{
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

void p_swap(int *x, int *y)
{
	int *temp;

	temp = x;
	x = y;
	y = temp;
}
