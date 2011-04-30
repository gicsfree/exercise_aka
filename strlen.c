#include <stdio.h>
int strlen(char *s1);
int main(int argc, const char *argv[])
{
	char a[6] = "hello";
	printf("%d\n", strlen(a));
	return 0;
}

int strlen(char *s1)
{
	int n = 0;
	while (*s1++)
		n++;
	return n;
}
