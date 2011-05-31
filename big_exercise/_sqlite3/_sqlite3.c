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
static void display(sqlite3 * db);
static void insert(sqlite3 * db);
static void delete(sqlite3 * db);
static void printf_func(void);
static void printf_delete(void);
static int select_func_num(void);
static int select_delete_num(void);
static void empty_cache(void);
static int is_name(char *str);
static int is_gender(char *str);
static int is_id(int id);
static int is_age(int age);
static void Gets(char str[], int n);

/* _sqlite3 */
void _sqlite3(char *str)
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
		switch (select_func_num()) {
		case 1:
			display(db);
			break;
		case 2:
			insert(db);
			break;
		case 3:
			delete(db);
			break;
		case 4:
			sqlite3_close(db);
			exit(0);
		}
	}
	sqlite3_close(db);

}

/* rscallback */
static int rscallback(void *p, int argc, char **argv, char **argvv)
{
	int i;

	*(int *) p = 0;
	for (i = 0; i < argc; i++)
		printf("%6s=%-8s ", argvv[i], argv[i] ? argv[i] : "NULL");
	putchar('\n');

	return 0;
}

/* create */
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

/* display */
static void display(sqlite3 * db)
{
	char *sql = NULL, *err = NULL;
	int empty = 1, ret;

	sql = sqlite3_mprintf("select * from employee;");
	ret = sqlite3_exec(db, sql, rscallback, &empty, &err);
	if (ret != SQLITE_OK) {
		fputs(err, stderr);
		fputs("\n", stderr);
	}
	if (empty)
		fputs("table employee is empty!\n", stderr);
	sqlite3_free(sql);
}

/* insert */
static void insert(sqlite3 * db)
{
	char *sql = NULL, *err = NULL, name[NAME_LEN], gender[GENDER_LEN];
	int id, age, ret;

	printf("input id:");
	while (0 == scanf("%d", &id) || 0 == is_id(id)) {
		empty_cache();
		system("clear");
		printf("\ninput id:");
	}
	printf("input name:");
	empty_cache();
	Gets(name, sizeof(name));
	while (0 == is_name(name)) {
		system("clear");
		printf("input name:");
		Gets(name, sizeof(name));
	}
	printf("input gender:");
	Gets(gender, sizeof(gender));
	while (0 == is_gender(gender)) {
		system("clear");
		printf("input gender:");
		Gets(gender, sizeof(gender));
	}
	printf("input age:");
	while (0 == scanf("%d", &age) || 0 == is_age(age)) {
		empty_cache();
		system("clear");
		printf("\ninput age:");
	}
	sql =
	    sqlite3_mprintf("insert into employee values(%d,%Q,%Q,%d);",
			    id, name, gender, age);
	ret = sqlite3_exec(db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fputs(err, stderr);
		fputs("\n", stderr);
	}
	sqlite3_free(sql);

}

/* delete */
static void delete(sqlite3 * db)
{
	char *sql = NULL, *err, name[NAME_LEN];
	int id, ret;

	switch (select_delete_num()) {
	case 1:
		printf("Please input the id:");
		while (0 == scanf("%d", &id) || 0 == is_id(id)) {
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
		Gets(name, sizeof(name));
		while (0 == is_name(name)) {
			system("clear");
			printf("Please input the name:");
			Gets(name, sizeof(name));
		}
		sql =
		    sqlite3_mprintf("delete from employee where name=%Q;",
				    name);
		break;
	}
	ret = sqlite3_exec(db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fputs(err, stderr);
		fputs("\n", stderr);
	}
	sqlite3_free(sql);

}

/* printf_func */
static void printf_func(void)
{
	printf("1.Display all records\n");
	printf("2.Insert Record\n");
	printf("3.Delete Record\n");
	printf("4.Exit\n");
	printf("Please Select[1-4]:");
}

/* select_func_num */
static int select_func_num(void)
{
	int nr = 0;

	while (nr < 1 || nr > 4) {
		printf_func();
		if (0 == scanf("%d", &nr)) {
			system("clear");
			empty_cache();
		}
	}
	system("clear");

	return nr;
}

/* printf_delete */
static void printf_delete(void)
{
	system("clear");
	printf("1.Delete by id\n");
	printf("2.Dlete by name\n");
	printf("Your choice[1-2]:");
}

/* select_delete_num */
static int select_delete_num(void)
{
	int nr = 0;

	while (nr < 1 || nr > 2) {
		printf_delete();
		if (0 == scanf("%d", &nr))
			empty_cache();
	}

	return nr;
}

/* empty_cache */
static void empty_cache(void)
{
	char ch;

	while ((ch = getchar()) != '\n');
}

/* is_name */
static int is_name(char *str)
{
	if (strlen(str) > NAME_LEN - 1 || strlen(str) == 0)
		return 0;
	while (*str) {
		if ((*str >= 'a' && *str <= 'z')
		    || (*str >= 'A' && *str <= 'Z') || *str == ' ')
			str++;
		else
			return 0;
	}

	return 1;
}

/* is_gender */
static int is_gender(char *str)
{
	if (strlen(str) > GENDER_LEN - 1
	    || (strcmp(str, MALE) != 0 && strcmp(str, FEMALE) != 0))
		return 0;

	return 1;
}

/* is_id */
static int is_id(int id)
{
	if (id < 1 || id > ID)
		return 0;

	return 1;
}

/* is_age */
static int is_age(int age)
{
	if (age < 1 || age > AGE)
		return 0;

	return 1;
}

/* Gets */
static void Gets(char str[], int n)
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
