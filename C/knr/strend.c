/* Function that return 1 if string t is at end of string s */

#include <stdio.h>
#include <string.h>

short unsigned
strend(char *s, char *t)
{
	s += strlen(s) - strlen(t);
	while (*s++ == *t++)
		if (*s == '\0')
			return 1;
	
	return 0;	
}

int
main(void)
{
	printf("%hu\n", strend("The quick brown fox jumps over the lazy dog", "dog"));
	printf("%hu\n", strend("Test string", "Ruby"));
	return 0;
}
