#include <stdio.h>

#define BUFFER_SIZE 4096

void
expand(char *clean, char *buffer)
{

	short unsigned j;
	short i;
	char ch = 0;
	
	for (i = 0, j = 0;buffer[i] != '\0';i++, j++) {
	
		if (buffer[i] == '-' && i > 0 && buffer[i + 1] != '\0') {
		
			j--;
			for (ch = buffer[i - 1];ch >= buffer[i - 1] && ch <= buffer[i + 1];ch++, j++)
				clean[j] = ch;
			i++;
		
		} else {
		
			clean[j] = buffer[i];
		
		}
	
	}

}

int
main()
{

	char buffer[BUFFER_SIZE/2] = {'\0'};
	char clean[BUFFER_SIZE] = {'\0'};
	char ch = 0;
	short unsigned i;
	
	for (i = 0;i < (BUFFER_SIZE / 2) - 1 && (ch = getchar()) != EOF;i++) 
		buffer[i] = ch;
	
	expand(clean, buffer);
	
	puts("\n");
	
	for (i = 0;i < BUFFER_SIZE - 1;i++)
		putchar(clean[i]);

	puts("\n");

	return 0;

}
