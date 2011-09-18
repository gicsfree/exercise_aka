#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
#include <cgi.h>

/* rscallback */
int rscallback(void *p, int argc, char **argv, char **argvv)
{
    *(int *)p = 0;

    return 0;
}

int main(void)
{
    sqlite3 *db;
    char *err = NULL;
    int ret = 0;
    int empty = 1;
    char *sql = NULL;
    char *data;

    cgi_init();
    cgi_process_form();

    cgi_init_headers(); //printf("Content-Type:text/html\r\n\r\n");
    puts("<html><head><title>login</title><meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\"></head><body>");

    if ((cgi_param("Name") == NULL) || (cgi_param("Password") == NULL))
    {
        puts("用户名或密码不正确，登录失败！");
        exit(1);
    }

#if 0
    printf("Name=%s\t", cgi_param("Name"));
    printf("Password=%s\t", cgi_param("Password"));
#endif

    ret = sqlite3_open("usr.db", &db);
    if (ret != SQLITE_OK)
    {
        puts(sqlite3_errmsg(db));
        puts("\n");
        exit(1);
    }

    sql = sqlite3_mprintf("select * from usr where name=%Q and password=%Q;", cgi_param("Name"), cgi_param("Password"));
    ret = sqlite3_exec(db, sql, rscallback, &empty, &err);
    if (ret != SQLITE_OK)
    {
        puts(err);
        puts("\n");
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_free(sql);

    if (empty != 0)
    {
        puts("用户名或密码不正确，登录失败！");
    }
    else
    {
        puts("登录成功！");
    }
    
    puts("</body></html>");
    cgi_end();
    sqlite3_close(db);

    return 0;
}
