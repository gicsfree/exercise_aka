#include <stdio.h>
#include <stdlib.h>

static int select_nr(void);
static void interface(void);
static void empty_cache(void);

static int select_nr(void)
{
	int nr = 0;

	while (nr < 1 || nr > 4) {
		interface();
		if (0 == scanf("%d", &nr)) {
			system("clear");
			empty_cache();
		}
	}
	system("clear");

	return nr;
}

static void interface(void)
{
	printf("1.Display all records\n");
	printf("2.Insert Record\n");
	printf("3.Delete Record\n");
	printf("4.Exit\n");
	printf("Please Select[1-4]:");
}

static void empty_cache(void)
{
	char ch;

	while ((ch = getchar()) != '\n');
}
