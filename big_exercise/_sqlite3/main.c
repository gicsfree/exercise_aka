#include <stdio.h>
#include <sqlite3.h>
#include "_sqlite3.h"

/* main */
int main(int argc, char *argv[])
{
	if (2 != argc) {
		printf("input:./file file.db\n");
		return 0;
	}
	_sqlite3(argv[1]);

	return 0;
}
