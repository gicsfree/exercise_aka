#include <stdio.h>

void foo(void)
{
	unsigned int a = 6;
	int b = -20;
	unsigned c = 0;

	printf("a + b = %d\n", a + b);
	printf("a + b = %u\n", a + b);
	(a + b > 6) ? puts("a + b > 6") : puts("a + b <= 6");	// signed converts to unsigned

	c = a + b;
	printf("c = %d\n", c);
	printf("c = %u\n", c);
}

int main(void)
{
	foo();

	return 0;
}
