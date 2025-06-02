#include <stdio.h>

int
add(int x, int y)
{
	return (x ^ y + ((x & y) << 1));
}

int
main()
{
	printf("%d", add(25, 34));
	return 0;
}
