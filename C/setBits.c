/* Function that returns x with the n bits that begin at position p set to the rightmost n bits of y */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

long long unsigned
setBits(long long unsigned x, short unsigned p, short unsigned n, long long unsigned y)
{
	long long unsigned mask = ~(~0 << n);
	y = (y & mask) << (p + 1 - n);
	x = x & ~(mask << (p + 1 - n));
	
	return x | y;
}

int
main(int argc, char **argv)
{
	if (argc != 5) {
		fputs("Usage:program [x] [p] [n] [y]\n", stderr);
		return 1;
	}

	printf("%llu\n", setBits(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));

	return 0;
}
