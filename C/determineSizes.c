/* Program to determine size of diferent types of numeric variables */

#include <stdio.h>

long long unsigned
pot(unsigned int x, unsigned int y)
{
	long long unsigned res = 1;
	while (y > 0) {
		res = res * x;
		y--;
	
	};

	return res;
}

int
main()
{
	long long unsigned ushort_s, short_s, uint_s, int_s, ulong_s, long_s; /* Variables to store types size in bytes */

	ushort_s = pot(2, sizeof(short) * 8) - 1;
	short_s = (pot(2, sizeof(short) * 8) - 1) / 2;
	uint_s = pot(2, sizeof(int) * 8) - 1;
	int_s = (pot(2, sizeof(int) * 8) - 1) / 2;
	ulong_s = pot(2, sizeof(long) * 8) - 1;
	long_s = (pot(2, sizeof(long) * 8) - 1) / 2;

	printf("Unsigned short: 0 to %llu\nShort: -%llu to %llu\nUnsigned int: 0 to %llu\n", ushort_s, short_s, short_s, uint_s);
	printf("Int: -%llu to %llu\nUnsigned long long: 0 to %llu\nLong long: -%llu to %llu\n", int_s, int_s, ulong_s, long_s, long_s);
	
	return 0;
}
