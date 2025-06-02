#include <ctype.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char **argv)
{
	char c;
	
	if (strcmp(argv[0], "./toLower") == 0)
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (strcmp(argv[0], "./toUpper") == 0)
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	else
		puts("The name of the command should be toLower or toUpper");

	return 0;
}
