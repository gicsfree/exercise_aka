#include <stdio.h>

int main()
{
	enum COLOR {
		RED,
		BLUE = 3,
		YELLOW
	};

	printf("%d\n", RED);
	printf("%d\n", YELLOW);

    return 0;
}
