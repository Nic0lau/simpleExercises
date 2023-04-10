/* Just a program that writes to stdout */

#include <stdio.h>

int
main(int argc, char **argv)
{
	while (--argc > 0)			
		printf("%s ", *++argv);

	putchar('\n');
	return 0;
}
