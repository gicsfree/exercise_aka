#include <stdio.h>

void encryption()
{
    char s[128];
    printf("input a string:");
    scanf("%s",s);
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

}
