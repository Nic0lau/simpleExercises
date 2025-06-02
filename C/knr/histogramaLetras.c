/* Program to create a histogram of printable ascii characters frequency */

#include <stdio.h>

#define BUFFER_SIZE 4096
#define MIN_CHAR_VAL 33
#define MAX_CHAR_VAL 126
#define PRINTABLE_CHARS_RANGE MAX_CHAR_VAL - MIN_CHAR_VAL + 1 

int
main()
{
	char buffer[BUFFER_SIZE] = {'\0'};
	char c;
	short unsigned printableChars[PRINTABLE_CHARS_RANGE] = {0};
	unsigned int i, j;

	for (i = 0;(c = getchar()) != EOF && i < BUFFER_SIZE;i++)
		buffer[i] = c;	
	
	puts("\n");
	
	for (i = 0;i < BUFFER_SIZE - 1;i++) 
		if (buffer[i] >= MIN_CHAR_VAL && buffer[i] <= MAX_CHAR_VAL)
			printableChars[buffer[i] - MIN_CHAR_VAL]++;

	for (i = 0;i < PRINTABLE_CHARS_RANGE;i++) {
		if (printableChars[i] != 0) {
			printf("\n%c| ", i + MIN_CHAR_VAL);
			for (j = 0;j < printableChars[i];j++)
				printf("-");
			printf(" | %u", printableChars[i]);
		}
	}
	
	printf("\n");
	
	return 0;
}
