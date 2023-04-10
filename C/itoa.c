/* Function that converts integer to ascii character */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

void
itoa(int n, char *s)
{
	static short unsigned i;
	
	if (s[0] == 0)
		i = 0;
	
	if (n < 0) {
		n = abs(n);
		s[i++] = '-';
	}
	
	if (n / 10 != 0)
		itoa(n / 10, s);
	
	s[i++] = (n % 10) + '0';
}

int
main(int argc, char **argv)
{
	char s[BUFFER_SIZE] = {'\0'};

	if (argc < 2) {
		fprintf(stderr, "Usage: program [numbers]\n");
		return 1;
	}

	for (argc--, argv++;argc > 0;argc--, argv++) {
		itoa(atoll(*argv), s);
		puts(s);
		memset(s, 0, sizeof(s));
	}

	return 0;
}
