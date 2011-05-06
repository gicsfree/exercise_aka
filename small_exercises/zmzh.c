#include <stdio.h>
char *zmzh(char *string);

int main(int argc, char *argv[])
{
	char a[128];
	printf("input :string\n");
	scanf("%s", a);
	printf("%s\n", zmzh(a));
	return 0;
}

char *zmzh(char *string)
{
	char *p = string;
	while (*p)
		if (*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z') {
			*p = (*p) ^ (0x01 << 5);
			p++;
		} else
			p++;
	return string;
}
