#include <stdio.h>
#include <stdlib.h>
#include "mycp.h"

int main(int argc, char *argv[])
{
	int choice;

	if (3 != argc) {
		printf("input: ./file src dest\n");
		return 0;
	}
	mycp(argv[1], argv[2]);

	return 0;
}
