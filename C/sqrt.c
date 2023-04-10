/* Program to print the square root of a number without the stdlib function */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double
pow(double x, double y)
{
	short unsigned i;
	double res = 1;
	
	for (i = 0;i < y;i++)
		res *= x;
	return res;
}

double
sqrt(double n)
{
	short unsigned i;
	srand(time(NULL));
	double y = rand();

	for (i = 0;i < 1000 && pow(y, 2) != n;i++)
		y = (y + n / y) / 2;

	return y;
}

int
main(int argc, char **argv)
{
	if (argc != 2) {
		fputs("Usage: program number\n", stderr);
		return 1;
	}
	
	printf("%lf\n", sqrt(atof(argv[1])));
	return 0;
}
