#include <stdio.h>
char *strcpy(char *dest, const char *src);
int main(int argc,char *argv[])
{
	char a[7], b[6] = "hello";
	strcpy(a, b);

	printf("%s\n", a);
	return 0;
}

char *strcpy(char *dest, const char *src)
{   char *p=dest;
	while (*src) {
		*p++ = *src++;
	}
	*p = '\0';
	return dest;
}
