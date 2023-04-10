/* Function to put the string t in the end of the string s */

#include <stdio.h>

void
strcat(char *s, char *t)
{
	while (*s != '\0')
		s++;
	
	while (*t != '\0')
		*s++ = *t++;
	
	*s = '\0';
}

int
main()
{
	char s[64] = "The quick brown fox ";

	strcat(s, "jumps over the lazy dog.");
	
	printf("%s\n", s);

	return 0;
}
