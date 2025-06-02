/* My own implementation of strncpy */

#include <stdio.h>

void
strncpy(char *s, short unsigned n, char *t)
{
	for (;n > 0;n--)
		*s++ = *t++;
}

int
main(void)
{
	char s[128] = "The quick brown fox ";
	
	strncpy(s, 10, "jumps over the lazy dog.");

	printf("%s\n", s);

	return 0;
}
