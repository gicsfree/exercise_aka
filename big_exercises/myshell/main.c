#include <stdio.h>
#include <stdlib.h>
#include "myshell.h"

int main(int argc, char *argv[])
{
	char str[128];
	printf("mysh%% ");
	while (strlen(gets(str)) > 0) {
		system("clear");
        printf("$:");
		puts(str);
		printf("show the command:\n");
		myshell(str);
		printf("mysh%% ");
	}

	return 0;
}
