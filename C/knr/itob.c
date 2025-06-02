/* Function that convert integer n in decimal base to b base */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32

void
itob(int n, char s[], short unsigned b)
{
	static short unsigned i;

	if (b < 2 || b > 36)
		return;
	
	if (s[0] == 0)
		i = 0;
	
	if (n < 0) {
		n = abs(n);
		s[i++] = '-';
	}

	if (n / b != 0)
		itob(n / b, s, b);
		
	s[i++] = (b <= 10 || n < 10 || n % b < 10) ? (n % b) + '0' : ((n % b) - 10) + 'A';
}


int
main(int argc, char **argv)
{
	char s[BUFFER_SIZE] = {'\0'};
	
	if (argc != 3) {
		fprintf(stderr, "Usage: program [number] [base]\n");
		return 1;
	}

	printf("10: %lld\n", atoll(argv[1]));
	itob(atoll(argv[1]), s, atoi(argv[2]));
	printf("%d: %s\n", atoi(argv[2]), s);
		
	return 0;
}
