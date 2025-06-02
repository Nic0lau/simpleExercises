/* Function to convert strings to double numbers */

#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 48

double pow(double, double);
double atof(char *s);

double
pow(double x, double y)
{
	double res = 1;
	short unsigned i;
	
	if (y < 0) {
		x = 1/x;
		y = -y;
	}
	
	for (i = 0;i < y;i++)
		res *= x;
	
	return res;
}

double
atof(char *s)
{
	double val;
	double pot = 1.0;
	short unsigned i = 0;
	short signal, exSignal, exp = 0;
	
	while (isspace(s[i])) /* Jumping spaces */
		i++;
	signal = (s[i] == '-') ? -1 : 1;
	
	if (s[i] == '+' || s[i] == '-')
		i++;
	
	for (val = 0.0;isdigit(s[i]);i++) /* Numbers before dot  */
		val = val * 10.0 + (s[i] - '0');
	
	if (s[i] == '.') { /* Numbers after dot */
		i++;
		for(;isdigit(s[i]);i++) {
			val = val * 10.0 + (s[i] - '0');
			pot *= 10.0;	
		}
	}

	val = signal * (val / pot);

	if (s[i] == 'E' || s[i] == 'e') { /* Scientific notation */	
		exSignal = (s[++i] == '-') ? -1 : 1;

		if (s[i] == '+' || s[i] == '-')
			i++;

		for (;isdigit(s[i]);i++)
			exp = exp * 10 + (s[i] - '0');

		exp *= exSignal;
		val *= pow(10, exp);	
	}

	return val;
}

int
main()
{
	char buffer[BUFFER_SIZE];
	char c;
	short unsigned i;
	
	for (i = 0;i < BUFFER_SIZE - 1 && (c = getchar()) != EOF;i++)
		buffer[i] = c;
	
	printf("\n%lf\n", atof(buffer));
	return 0;
}
