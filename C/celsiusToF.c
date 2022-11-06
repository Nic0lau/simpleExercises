/* Celsius to Fahrenheit converter */

#include <stdio.h>

#define LIMIT 1000
#define PROGRESSION -1

int
main()
{

	float fahr;
	int celsius, prog;
	
	prog = PROGRESSION;
	for(celsius = LIMIT; celsius >= 0; celsius = celsius + prog) {
	
		fahr = celsius * (9.0/5.0) + 32.0;
		printf("%4d\t%6.2f\n", celsius, fahr);
	
	};

	return 0;
};
