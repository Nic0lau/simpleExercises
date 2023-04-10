/* My implementation of strncat function */

#include <stdio.h>

void
strncat(char *s, short unsigned n, char *t)
{
	while (*s != '\0')
		s++;
	
	while (n-- > 0)
		*s++ = *t++;

	*s = '\0';
}

int
main(void)
{
	char s[64] = "The quick brown fox ";
	
	strncat(s, 5, "jumps over the lazy dog");
	
	printf("%s\n", s);
	
	return 0;
}
