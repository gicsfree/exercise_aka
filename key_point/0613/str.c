#include <stdio.h>

char *GetMemory0(void)
{
	char p[] = "Hello World"; 

	return p;
}

char *GetMemory1(void)
{
	const char p[] = "Hello World";

	return p;
}

char *GetMemory2(void)
{
	char *p = "Hello World";

	return p;
}

void Test(void)
{
	char *str = NULL;

	str = GetMemory0();
	puts(str);

	str = GetMemory1();
	puts(str);

	str = GetMemory2();
	puts(str);

}

void main()
{
	Test();
}
