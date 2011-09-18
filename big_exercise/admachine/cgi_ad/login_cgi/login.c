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

    cgi_init();
    cgi_process_form();

    if ((cgi_param("UserName") == NULL) || (cgi_param("Password") == NULL))
    {
        cgi_redirect("/httpd_ad/login_error.html");
        exit(1);
    }

    #if 0
    printf("Name=%s\t", cgi_param("Name"));
    printf("Password=%s\t", cgi_param("Password"));
    #endif

    ret = sqlite3_open("user.db", &db);
    if (ret != SQLITE_OK)
    {
        puts(sqlite3_errmsg(db));
        exit(1);
    }

    sql = sqlite3_mprintf("select * from user where username=%Q and password=%Q;", cgi_param("UserName"), cgi_param("Password"));
    ret = sqlite3_exec(db, sql, rscallback, &empty, &err);
    if (ret != SQLITE_OK)
    {
        puts(err);
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_free(sql);

    if (empty != 0)
    {
        cgi_redirect("/httpd_ad/login_error.html");
    }
    else
    {
        cgi_session_register_var("logged", "1");
        cgi_redirect("/httpd_ad/main.html");
    }
    
    cgi_end();
    sqlite3_close(db);

    return 0;
}
