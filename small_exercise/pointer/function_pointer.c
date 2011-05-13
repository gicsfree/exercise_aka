#include <stdio.h>

/* 函数指针+结构体 实现C++ */
/*  函数指的针参数和返回值，必须和函数原型相同 */
void say_hello(const char *str)
{
	printf("Hello %s\n", str);
}

typedef void (*f_t) (const char *);
typedef void f_tt(const char *);

int main(int argc, char *argv[])
{
	void (*f) (const char *) = say_hello;
	f_t f1 = say_hello;
	f_tt *f2 = say_hello;

	f("Mike");
	(*f) ("Mike");
	f1("Mike");
	f2("Mile");

	return 0;
}
