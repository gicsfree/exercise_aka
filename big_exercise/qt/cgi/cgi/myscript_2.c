#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cgi.h"

int main(void)
{
    char *data;
    cgi_init();
    cgi_process_form();

    cgi_init_headers(); //printf("Content-Type:text/html\r\n\r\n");
    puts("<html><body>");

    puts("<img src=\"/images/arc.jpg\">");

    if (cgi_param("Name"))
    {
        printf("Name=%s\t", cgi_param("Name"));
    }
    if (cgi_param("Gender"))
    {
        printf("Gender=%s\t", cgi_param("Gender"));
    }
    while ((data = cgi_param_multiple("like")) != NULL)
    {
        puts(data);
    }

    puts("</body></html>");
    cgi_end();

    return 0;
}
