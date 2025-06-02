/* My implementation of strncmp function */

#include <stdio.h>

short
strncmp(char *s, short unsigned n, char *t)
{
	for (;*s == *t && n > 0 && *s != '\0';s++, t++, n--);
	
	return *s - *t;
}

int
main(void)
{
	printf("%hd\n", strncmp("String one", 10, "String two"));
	printf("%hd\n", strncmp("Big string", 5, "Small string"));
	printf("%hd\n", strncmp("Big string", 12, "Small string"));
	printf("%hd\n", strncmp("Limao um", 5, "Limao dois"));
	
	return 0;
}
