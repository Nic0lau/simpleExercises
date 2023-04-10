/* Program to invert a specific range of bits of a number */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 21

long long
invertBits(long long x, short unsigned p, short unsigned n)
{
	return (x ^ (~(~0 << n) << (p + 1 - n)));
}

int
main()
{
	char buffer[BUFFER_SIZE] = {'\0'};
	char c;
	short unsigned i;
	
	puts("Insert the number:");
	
	for (i = 0;i < BUFFER_SIZE - 1 && (c = getchar()) != '\n';i++)
		buffer[i] = c;

	printf("\n%lld\n", atoll(buffer));
	printf("%lld\n", invertBits(atoll(buffer), 4, 3));

	return 0;	
}
