/* Function to remove every character of the string x that is contained in string y*/

#include <stdio.h>

#define BUFFER_SIZE 4096

void
removeChar(char *origin, char *remove)
{
	short unsigned i, j;
	
	for (i = 0;origin[i] != '\0';i++)
		for (j = 0;remove[j] != '\0';j++)
			if (origin[i] == remove[j]) {
				origin[i] = '\0';
				break;
			}
}

int
main()
{
	char buffer[BUFFER_SIZE] = {'\0'};
	char remove[BUFFER_SIZE / 8] = {'\0'};
	char c;
	short unsigned i;

	puts("Write the string with the forbidden characters:");
	
	for (i = 0;i < (BUFFER_SIZE / 8) - 1 && (c = getchar()) != '\n' && c != EOF;i++)
		remove[i] = c;
	remove[i] = '\0';

	putchar('\n');
	puts("Write the string to be cleaned:");
	
	for (i = 0;i < BUFFER_SIZE - 1 && (c = getchar()) != '\n' && c != EOF;i++)
		buffer[i] = c;	
	buffer[i] = '\0';
	
	removeChar(buffer, remove);
	
	putchar('\n');
	
	for (i = 0;i < BUFFER_SIZE;i++)
		if (buffer[i] != '\0')
			putchar(buffer[i]);
	
	putchar('\n');
	
	return 0;
}
