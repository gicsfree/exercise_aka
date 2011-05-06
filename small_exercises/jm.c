#include <stdio.h>
char *jm(char *string);

int main(int argc, char *argv[])
{
	char t[20];
	printf("input :string\n");
	scanf("%s", t);
	jm(t);
	return 0;
}

char *jm(char *string)
{
	char *p = string, *q = string;
	printf("jiamiqian :%s\n", p);
	while (*p) {
		*p = *p ^ 'x';
		p++;
	}
	printf("jiamihou :%s\n", string);
	while (*q) {
		*q = *q ^ 'x';
		q++;
	}
	printf("jiemihou :%s\n", string);

	return string;
}
