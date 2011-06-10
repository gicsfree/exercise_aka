#include <stdio.h>

#define _U

/* check cpu endin */
#ifdef U
int check_cpu_endian(void)
{
	union w {
		int a;
		char b;
	} c;			// members of union begin to store from low address

	c.a = 0x11223344;

	return (c.b == 0x44);
}

#else
int check_cpu_endian(void)
{
	int data = 0x11223344;

	if (*(char *) &data == 0x44) {
		return 1;
	} else {
		return 0;
	}
}
#endif

/* main */
int main(int argc, const char *argv[])
{

	int ret = check_cpu_endian();

	if (ret == 1) {
		printf("little-endin\n");
	} else {
		printf("big-endin\n");
	}

	return 0;
}
