#include <stdio.h>
char *letter_switch(char *string);

int main(int argc, char *argv[])
{
	char a[128];
	printf("input :string\n");
	scanf("%s", a);
	printf("%s\n", letter_switch(a));
	return 0;
}

char *letter_switch(char *string)
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
