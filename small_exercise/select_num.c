#include <stdio.h>

static int select_num(void);
static void printf_func(void);
static void empty_cache(void);

int main(void)
{
	while (1) {
		switch (select_num()) {
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			return 0;

		}
	}

	return 0;
}

static int select_num(void)
{
	int num = 0, ret;

	while (num < 1 || num > 4) {
		printf_func();
		ret = scanf("%d", &num);
		if (ret != 1)
			empty_cache();
	}

	return num;
}

static void printf_func(void)
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
