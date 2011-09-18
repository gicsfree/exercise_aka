#include <stdio.h>
#include <cgi.h>

int main(void)
{
    cgi_init();

    if (cgi_session_var_exists("logged") == 1)
    {
        cgi_session_unregister_var("logged");
    }	
    cgi_redirect("/httpd_ad/login.html");
    
    cgi_end();

    return 0;
}
