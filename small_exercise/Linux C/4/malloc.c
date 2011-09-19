#include <stdio.h>
#include <stdlib.h>

void alter(int ** p)
{
	int *q;
	
	q = (int *)malloc(sizeof(int)); 

	*q = 100; 
	*p = q; 
}

int main(void)
{
	int a;
	int *p;

	a = 10; 
	p = &a; 

	printf("p : 0x%x, *p %d\n", (unsigned int)p, *p);
	alter(&p); 
	printf("p : 0x%x, *p %d\n", (unsigned int)p, *p);

	return 0;
}
