#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;

    dir = opendir("../ls");
    while ((ptr = readdir(dir)) != NULL){
        lstat(ptr->d_name, &buf);
        if (S_ISDIR(buf.st_mode))
            printf("d");
        else if (S_ISREG(buf.st_mode))
            printf("-");
        else if (S_ISLNK(buf.st_mode))
            printf("l");

        if (S_IRUSR == 00400)
            printf("r");
        else 
            printf("-");
        if (S_IWUSR == 00200)
            printf("w");
        else
            printf("-");
        if (S_IXUSR == 00100)
            printf("x");
        else
            printf("-");

        if (S_IRGRP == 00040)
            printf("r");
        else 
            printf("-");
        if (S_IWGRP == 00020)
            printf("w");
        else
            printf("-");
        if (S_IXGRP == 00010)
            printf("x");
        else
            printf("-");

        if (S_IROTH == 00004)
            printf("r");
        else 
            printf("-");
        if (S_IWOTH == 00002)
            printf("w");
        else
            printf("-");
        if (S_IXOTH == 00001)
            printf("x");
        else
            printf("-");

        printf(" ");
//        printf("%s", buf.st_dev);
        printf(" ");

//        printf("%d", buf.st_uid);
        printf(" ");

//        printf("%s", buf.st_gid);
        printf(" ");

//        printf("%d\n", buf.st_size);
        printf("%s\n", ptr->d_name);
    }

    closedir(dir);

    return 0;
}
