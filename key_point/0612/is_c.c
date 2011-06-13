#include <stdio.h>

int main(int argc, const char *argv[])
{
#ifdef _cplusplus
	printf("C++\n");
#else
	printf("C\n");
#endif

	return 0;
}
