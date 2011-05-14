#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int rscallback(void *p, int argc, char **argv, char **argvv);
static char *display(void);
static char *insert(void);
static char *delete(void);
static void interface(void);
static void interface1(void);
static int select_nr(void);
static int select_nr1(void);
static void empty_cache(void);

int _sqlite3(char *str)
{
	sqlite3 *db = NULL;
	char *err = NULL, *sql = NULL;
	int ret = 0;

	system("clear");
	ret = sqlite3_open(str, &db);
	if (ret != SQLITE_OK) {
		fputs(sqlite3_errmsg(db), stderr);
		fputs("\n", stderr);
		exit(1);
	}
	while (1) {
		int flag = 0, empty = 1;

		switch (select_nr()) {
		case 1:
			sql = display();
			flag = 1;
			break;
		case 2:
			sql = insert();
			break;
		case 3:
			sql = delete();
			break;
		case 4:
			return 0;
		}
		ret = sqlite3_exec(db, sql, rscallback, &empty, &err);
		if (ret != SQLITE_OK) {
			fputs(err, stderr);
			fputs("\n", stderr);
			sqlite3_close(db);
			exit(1);
		}
		if (empty && 1 == flag)
			fputs("table employee is empty\n", stderr);
	}
	sqlite3_close(db);

	return 0;
}

static int rscallback(void *p, int argc, char **argv, char **argvv)
{
	int i;

	*(int *) p = 0;
	for (i = 0; i < argc; i++)
		printf("%6s=%-8s ", argvv[i], argv[i] ? argv[i] : "NULL");
	putchar('\n');

	return 0;
}

static char *display(void)
{
	char *sql = NULL;

	sql = sqlite3_mprintf("select * from employee;");

	return sql;
}

static char *insert(void)
{
	char *sql = NULL, name[15], gender[10];
	int id, age;

	printf("input id:");
	while (0 == scanf("%d", &id)) {
		empty_cache();
		printf("\ninput id:");
	}
	printf("input name:");
	scanf("%s", name);
	printf("input gender:");
	scanf("%s", gender);
	printf("input age:");
	while (0 == scanf("%d", &age)) {
		empty_cache();
		printf("\ninput age:");
	}
	sql =
	    sqlite3_mprintf("insert into employee values(%d,%Q,%Q,%d);",
			    id, name, gender, age);

	return sql;
}

static char *delete(void)
{
	char *sql = NULL, name[15];
	int id;

	switch (select_nr1()) {
	case 1:
		printf("Please input the id:");
		while (0 == scanf("%d", &id)) {
			empty_cache();
			printf("\nPleade input the id:");
		}
		sql =
		    sqlite3_mprintf("delete from employee where id=%d;",
				    id);
		break;
	case 2:
		printf("Please input the name:");
		scanf("%s", name);
		sql =
		    sqlite3_mprintf("delete from employee where name=%Q;",
				    name);
		break;
	}

	return sql;
}

static void interface(void)
{
	printf("1.Display all records\n");
	printf("2.Insert Record\n");
	printf("3.Delete Record\n");
	printf("4.Exit\n");
	printf("Please Select[1-4]:");
}

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

static void interface1(void)
{
	system("clear");
	printf("1.Delete by id\n");
	printf("2.Dlete by name\n");
	printf("Your choice[1-2]:");
}

static int select_nr1(void)
{
	int nr = 0;

	while (nr < 1 || nr > 2) {
		interface1();
		if (0 == scanf("%d", &nr))
			empty_cache();
	}

	return nr;
}

static void empty_cache(void)
{
	char ch;

	while ((ch = getchar()) != '\n');
}
