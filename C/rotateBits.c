/* Function that rotate the right n bits of x to the left */

#include <stdio.h>
#include <stdlib.h>

long long unsigned
rotBitRight(long long unsigned x, short unsigned n)
{
	long long unsigned y;
	
	y = x >> n;
	x = x << ((sizeof(x) * 8) - n);

	return x | y;
}

int
main(int argc, char **argv)
{
	if (argc < 3) {
		fputs("Usage:program [x] [n]\n", stderr);
		return 1;
	}
	
	printf("\n%llu\n", rotBitRight(atoll(argv[1]), atoll(argv[2])));
	return 0;
}
