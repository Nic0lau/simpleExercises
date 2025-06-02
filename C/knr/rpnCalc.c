/* Reverse polish calculator */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 64
#define BUFFER_SIZE 128
#define VAR_AMOUNT 27

short unsigned getLine(char *s, short unsigned lim);
char getop(char *s);
double pop(void);
void push(double v);
void showStackTop(void);
void swapStackTop(void);
void duplicateStackTop(void);
void clearStack(void);

char line[BUFFER_SIZE * 2] = {'\0'};
short unsigned linei = 0;
short sp = 0;
double stack[STACK_SIZE] = {'\0'};
double vars[VAR_AMOUNT] = {0.0};

short unsigned
getLine(char *s, short unsigned lim)
{
	short unsigned i;
	char ch;
	
	for (i = 0;i < lim - 1 && (ch = getchar()) != EOF && ch != '\n';i++)
		*(s + i) = ch;
	
	if (ch == '\n')
		*(s + i) = '\n';
	
	s[++i] = '\0';
	
	return i;
}

char
getop(char *s)
{
	short unsigned i = 0;
	char ch;

	if (line[linei] == '\0')
		if (getLine(line, BUFFER_SIZE * 2) == 0)
			return EOF;
		else
			linei = 0;
	
	while ((s[0] = ch = line[linei++]) == ' ' || ch == '\t');
	
	s[1] = '\0';
	
	if (ch >= 'A' && ch <= 'Z')
		if (line[linei] == ' ' && line[linei + 1] == '=')
			return '=';
		else
			return ch;
	
	if (!isdigit(ch) && ch != '.' && ch != '-')
		return ch;
	
	if (ch == '-') {
	
		if (!isdigit(line[linei]) && line[linei] != '.')
			return ch;
		ch = line[linei];
		linei++;
		s[++i] = ch;
	
	}
	
	if (isdigit(ch))
		while (isdigit(s[++i] = ch = line[linei++]));

	if (ch == '.')
		while (isdigit(s[++i] = ch = line[linei++]));
	
	s[i] = '\0';
	
	if (ch != EOF)
		linei--;

	return '0';
}

double
pop(void)
{
	if (sp > 0) {
		return stack[--sp];
	} else {
		printf("\nError: Empty stack\n");
		return 0.0;
	}
}

void
push(double v)
{
	if (sp < STACK_SIZE)
		stack[sp++] = v;
	else
		printf("\nError: Stack is full\n");
}

void
showStackTop(void)
{
	if (sp > 0)
		printf("\t%lf\n", stack[sp - 1]);
	else
		printf("Error: Empty stack");
}

void
swapStackTop(void)
{
	double swp;
	
	swp = stack[sp - 1];
	stack[sp - 1] = stack[sp - 2];
	stack[sp - 2] = swp;
}

void
duplicateStackTop(void)
{
	push(stack[sp - 1]);
}

void
clearStack(void)
{
	sp = 0;
}

int
main(void)
{
	char buffer[BUFFER_SIZE];
	char currentLetter = 0;
	double op2;
	short type;
		
	while ((type = getop(buffer)) != EOF) {
	
		switch (type) {
		
		case '0':
			push(atof(buffer));
			break;
		case 'A'...'Z':
			currentLetter = type - 'A';
			push(vars[currentLetter]);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("Error: Cannot divide by zero\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push(fmod(pop(), op2));
			else
				printf("Error: Cannot divide by zero\n");
			break;
		case '!':
			showStackTop();
			break;
		case '@':
			swapStackTop();
			break;
		case '#':
			duplicateStackTop();
			break;
		case '$':
			clearStack();
			break;
		case '&':
			push(sin(pop()));
			break;
		case '\\':
			push(exp(pop()));
			break;
		case '^':
			op2 = pop();
			push(pow(pop(), op2));
			break;
		case '=':
			vars[currentLetter] = stack[sp - 1];
			break;
		case '\n':
			printf("\t%lf\n", pop());
			break;
		default:
			printf("Error: %s is an unknown command\n", buffer);
			break;
		
		}	
	}

	return 0;
}
