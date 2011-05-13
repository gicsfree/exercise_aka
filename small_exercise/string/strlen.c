#include <stdio.h>
int strlen(const char *s1);
int main(int argc,char *argv[])
{
	char a[6] = "hello";
	printf("%d\n", strlen(a));
	return 0;
}

int strlen(const char *s1)
{
	int n = 0;
	while (*s1++)
		n++;
	return n;
}
