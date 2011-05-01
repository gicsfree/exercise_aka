#include <stdio.h>
char *strcat(char *s1, const char *s2);
int main(int argc, const char *argv[])
{
	char a[6] = "hello", b[6] = "hello";
	strcat(a, b);
	printf("%s\n", a);

	return 0;
}

char *strcat(char *s1, const char *s2)
{   char *p=s1;
	while (*p++);
	p--;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return s1;
}
