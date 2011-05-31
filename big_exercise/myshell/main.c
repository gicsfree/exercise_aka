#include <stdio.h>
#include <string.h>
#include "myshell.h"

#define LEN 128

/* Gets */
void Gets(char str[], int n)
{
	char s[n];
	int i = 0;

	fgets(s, n, stdin);

	while ((s[i] != '\n') && (s[i] != '\0')) {
		*str++ = s[i];
		i++;
	}
	*str = '\0';
}

/* main */
int main(int argc, char *argv[])
{
	char str[LEN];

	printf("mysh%% ");
	Gets(str, sizeof(str));

	while (strlen(str) > 0) {
		myshell(str);
		printf("mysh%% ");
		Gets(str, sizeof(str));
	}

	return 0;
}
