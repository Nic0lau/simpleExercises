/* Program to escape characters like tabs and new lines */

#include <stdio.h>

#define BUFFER_SIZE 4096

void
escape(char *s, char *t)
{

	short unsigned i, j;
		
	for (i = 0, j = 0;t[i] != '\0';i++)
		switch (t[i]) {
		
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		default:
			s[j++] = t[i];
			break;
		
		};

}

int
main()
{

	char buffer[BUFFER_SIZE] = {'\0'};
	char cleanBuffer[BUFFER_SIZE] = {'\0'};
	short unsigned i;
	char ch = 0;
	
	for (i = 0;i < BUFFER_SIZE - 1 && (ch = getchar()) != EOF;i++)
		buffer[i] = ch;

	escape(cleanBuffer, buffer);
	
	for (i = 0;cleanBuffer[i] != '\0';i++)
		putchar(cleanBuffer[i]);
	
	putchar('\n');
	return 0;

}
