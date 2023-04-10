/* Program to count how much ones a number have in binary representation */

#include <stdio.h>
#include <stdlib.h>

short unsigned
count1(long long unsigned x)
{
	short unsigned i;
	
	for (i = 0;x != 0;i++)
		x &= x - 1;

	return i;
}

int
main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: program [number]\n");
		return 1;
	}

	printf("%hu\n", count1(atoll(*++argv)));
	return 0;
}
