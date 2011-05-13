#include <stdio.h>
char *encrypt(char *s);

int main(int argc, char *argv[])
{
	char string[128];
	printf("input :string\n");
	scanf("%s", string);
	encrypt(string);
	return 0;
}

char *encrypt(char *s)
{
	char *p = s, *q = s;
	printf("encrypt_before is :%s\n", s);
	while (*p) {
		*p = *p ^ 'x';
		p++;
	}
	printf("encrypted is      :%s\n", s);
	while (*q) {
		*q = *q ^ 'x';
		q++;
	}
	printf("decrypted is      :%s\n", s);

	return s;
}
