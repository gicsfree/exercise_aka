#include <stdio.h>

int main(void)
{
    int a[5] = {0, 1, 2, 3, 4};
    int b = 4;
    int c = 5;
    int d;
    int e;
    int *ptr = (int *)(&a + 1);
    
    d = b, c;
    e = (b, c);
    printf("d = %d\n", d);
    printf("e = %d\n", e);   
    printf("*(a + 1) = %d\n", *(a + 1));
    printf("*(ptr - 1) = %d\n", *(ptr - 1)); 

    return 0;
}
