#include <stdio.h>
#define PRINT_INT(x) printf(#x"=%d\n",x)

int main(int argc, char *argv[])
{
	printf("this is \
cool,is\
 it?\n");
	printf("%c\n", '\046');
	printf("hello" "world\n");
	printf(__FILE__ "\n");
	printf("%d\n", __LINE__);
	printf("%s\n", __FILE__);
	printf("%s\n", __DATE__);
	printf("%s\n", __TIME__);
	printf("%d\n", __STDC__);	/* 支持C语言标准 */
	printf("%s\n", __func__);
	PRINT_INT(3 + 5);

	return 0;
}
