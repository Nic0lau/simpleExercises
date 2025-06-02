/* Celsius to Fahrenheit convert */

#include <stdio.h>

#define LIMIT 1000
#define PROGRESSION 1

static void celsiusToFahrenheit(unsigned int limit, unsigned int prog);

static void
celsiusToFahrenheit(unsigned int limit, unsigned int prog)
{
	float fahr;
	unsigned int celsius;
	
	for (celsius = 0;celsius <= limit;celsius += prog) {
		fahr = celsius * (9.0/5.0) + 32.0;
		printf("%4d\t%6.2f\n", celsius, fahr);
	}
}

int
main()
{
	celsiusToFahrenheit(LIMIT, PROGRESSION);
	
	return 0;
}
