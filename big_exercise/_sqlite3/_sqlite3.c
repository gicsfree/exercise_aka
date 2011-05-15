#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#define NAME_LEN 15
#define GENDER_LEN 7
#define MALE "male"
#define FEMALE "female"
#define ID 120
#define AGE 120

static int rscallback(void *p, int argc, char **argv, char **argvv);
static void create(sqlite3 * db);
static int display(sqlite3 * db);
static int insert(sqlite3 * db);
static int delete(sqlite3 * db);
static void interface(void);
static void interface1(void);
static int select_nr(void);
static int select_nr1(void);
static void empty_cache(void);
static int is_name(char *str);
static int is_gender(char *str);
static int is_id(int id);
static int is_age(int age);

int _sqlite3(char *str)
{
	sqlite3 *db = NULL;
	int ret;

	system("clear");
	ret = sqlite3_open(str, &db);
	if (ret != SQLITE_OK) {
		fputs(sqlite3_errmsg(db), stderr);
		fputs("\n", stderr);
		exit(1);
	}
	create(db);
	while (1) {
		switch (select_nr()) {
		case 1:
			if (0 != display(db)) {
				printf("An error occurred!\n");
				sqlite3_close(db);
				exit(1);
			}
			break;
		case 2:
			if (0 != insert(db)) {
				printf("An error occurred!\n");
				sqlite3_close(db);
				exit(1);
			}
			break;
		case 3:
			if (0 != delete(db)) {
				printf("An error occurred!\n");
				sqlite3_close(db);
				exit(1);
			}
			break;
		case 4:
			sqlite3_close(db);
			exit(0);
		}
	}
	sqlite3_close(db);
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

static void create(sqlite3 * db)
{
	char *sql = NULL;
	int ret;

	sql = sqlite3_mprintf("select * from employee;");
	ret = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (ret != SQLITE_OK) {
		sqlite3_exec(db,
			     "create table employee(id integer primary key,name text,gender text,age integer);",
			     NULL, NULL, NULL);
		system("clear");
	}
	sqlite3_free(sql);

}

static int display(sqlite3 * db)
{
	char *sql = NULL;
	int empty = 1, ret;

	sql = sqlite3_mprintf("select * from employee;");
	ret = sqlite3_exec(db, sql, rscallback, &empty, NULL);
	if (empty)
		fputs("table employee is empty!\n", stderr);
	sqlite3_free(sql);

	return ret;
}

static int insert(sqlite3 * db)
{
	char *sql = NULL, name[NAME_LEN], gender[GENDER_LEN];
	int id, age, ret;

	printf("input id:");
	while (0 == scanf("%d", &id) || 1 == is_id(id)) {
		empty_cache();
		system("clear");
		printf("\ninput id:");
	}
	printf("input name:");
	empty_cache();
	gets(name);
	while (1 == is_name(name)) {
		system("clear");
		printf("input name:");
		gets(name);
	}
	printf("input gender:");
	gets(gender);
	while (1 == is_gender(gender)) {
		system("clear");
		printf("input gender:");
		gets(gender);
	}
	printf("input age:");
	while (0 == scanf("%d", &age) || 1 == is_age(age)) {
		empty_cache();
		system("clear");
		printf("\ninput age:");
	}
	sql =
	    sqlite3_mprintf("insert into employee values(%d,%Q,%Q,%d);",
			    id, name, gender, age);
	ret = sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_free(sql);

	return ret;
}

static int delete(sqlite3 * db)
{
	char *sql = NULL, name[NAME_LEN];
	int id, ret;

	switch (select_nr1()) {
	case 1:
		printf("Please input the id:");
		while (0 == scanf("%d", &id) || 1 == is_id(id)) {
			empty_cache();
			printf("\nPleade input the id:");
		}
		sql =
		    sqlite3_mprintf("delete from employee where id=%d;",
				    id);
		break;
	case 2:
		printf("Please input the name:");
		empty_cache();
		gets(name);
		while (1 == is_name(name)) {
			system("clear");
			printf("Please input the name:");
			gets(name);
		}
		sql =
		    sqlite3_mprintf("delete from employee where name=%Q;",
				    name);
		break;
	}
	ret = sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_free(sql);

	return ret;
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

static int is_name(char *str)
{
	if (strlen(str) > NAME_LEN - 1)
		return 1;
	while (*str) {
		if ((*str >= 'a' && *str <= 'z')
		    || (*str >= 'A' && *str <= 'Z') || *str == ' ')
			str++;
		else
			return 1;
	}

	return 0;
}

static int is_gender(char *str)
{
	if (strlen(str) > GENDER_LEN - 1
	    || (strcmp(str, MALE) != 0 && strcmp(str, FEMALE) != 0))
		return 1;

	return 0;
}

static int is_id(int id)
{
	if (id < 1 || id > ID)
		return 1;

	return 0;
}

static int is_age(int age)
{
	if (age < 1 || age > AGE)
		return 1;

	return 0;
}
