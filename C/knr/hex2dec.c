/* Program to convert hexadecimal to decimal */

#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE 64

long long unsigned htoi(char *s);

long long unsigned
htoi(char *s)
{
	long long unsigned val;
	short current;
	short unsigned i;
	
	for (val = 0, i = 0;s[i] != '\0';i++) {
		current = (isdigit(s[i])) ? s[i] - '0' :
		    (s[i] >= 'A' && s[i] <= 'F') ? s[i] - 'A' + 10 :
		    s[i] - 'a' + 10;
		val = val * 16 + current;
	}

	return val;
}

int
main()
{
	char buffer[BUFFER_SIZE];
	char c;
	short unsigned i = 0;

	while (i < BUFFER_SIZE - 1 && (c = getchar()) != EOF)
		if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || isdigit(c))
			buffer[i++] = c;

	buffer[i] = '\0';
	
	printf("\n\n%llu\n\n", htoi(buffer));
	return 0;
}
