#include <stdio.h>
#include "myshell.h"

int main(int argc, char *argv[])
{
	char str[128];
	printf("mysh%% ");
	while (strlen(gets(str)) > 0) {
		printf("show the command:\n");
		myshell(str);
		printf("mysh%% ");
	}

	return 0;
}
