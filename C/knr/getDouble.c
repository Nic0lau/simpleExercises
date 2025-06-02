/* Program to convert numbers from stdin to double an put them in an array */

#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE 16
#define OVERFLOW_BUFFER_SIZE 8

char getch(void);
void ungetch(char ch);
short getDouble(double *n);

char overflowChars[OVERFLOW_BUFFER_SIZE] = {'\0'};
short unsigned overflowPointer = 0;

char
getch(void)
{
	return (overflowPointer > 0) ? overflowChars[--overflowPointer] : getchar();
}

void
ungetch(char ch)
{
	if (overflowPointer >= OVERFLOW_BUFFER_SIZE)
		printf("Error: Too many chars");
	else
		overflowChars[overflowPointer++] = ch;
}

short
getDouble(double *n)
{
	char ch;
	short signal;
	double pot = 1.0;
	
	while (isspace(ch = getch()));
	
	if (!isdigit(ch) && ch != EOF && ch != '-' && ch != '+') {	
		ungetch(ch);
		return 0;
	}

	signal = (ch == '-') ? -1 : 1;
	
	if (ch == '+' || ch == '-') {	
		ch = getch();
		if (!isdigit(ch)) {
			ungetch(ch);
			ungetch((signal == 1) ? '+' : '-');
			return 0;
		}
	}
	
	for (*n = 0.0;isdigit(ch);ch = getch())
		*n = 10.0 * *n + (ch - '0');
	
	if (ch == '.') {
		ch = getch();
		while (isdigit(ch)) {	
			*n = *n * 10.0 + (ch - '0');
			pot *= 10.0;
			ch = getch();
		
		}
	}
	
	*n = signal * (*n / pot);
	
	if (ch != EOF)
		ungetch(ch);

	return ch;
}

int
main()
{
	short unsigned i;
	double buffer[BUFFER_SIZE] = {0.0};
		
	for (i = 0;i < BUFFER_SIZE && getDouble(&buffer[i]) != EOF;i++);
	
	for (i = 0;i < BUFFER_SIZE;i++)
		printf("%lf\n", buffer[i]);
	
	return 0;
}
