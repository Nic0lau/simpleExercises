/* Print longest line from a text */

#include <stdio.h>

#define MAX_LINE_SIZE 8192

void
copyArray(char *from, char *to)
{
	short unsigned i;
	
	for (i = 0;from[i] != '\0';i++)
		to[i] = from[i];
	to[i] = '\0';
}

int
main()
{
	char buffer[MAX_LINE_SIZE] = {'\0'};
	char c;
	short unsigned i;
	char longest[MAX_LINE_SIZE] = {'\0'};
	short unsigned bigSize, size;

	size = bigSize = 0;
	
	for (i = 0;i < MAX_LINE_SIZE - 1;i++) {
		
		c = getchar();
		if (c == '\n' || c == EOF) {

			if (size > bigSize) {
				bigSize = size;
				buffer[i] = '\0';
				copyArray(buffer, longest);
				i = -1;
			}

			size = 0;
		} else {
			size++;
			buffer[i] = c;
		}	
	}

	printf("\nThe biggest line was: %s\n", longest);	
}
