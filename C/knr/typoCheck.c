/* Program to check rudimentary typos in C code */

#include <stdio.h>

#define BUFFER_SIZE 4096

int
main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	long long apostrophe, bracket, comment, curly, parenthesis, quote;
	FILE *fp;
	short unsigned i;
	
	if (argc < 2) {
		fputs("Usage:program [files]\n", stderr);
		return 1;
	}

	apostrophe = bracket = comment = curly = parenthesis = quote = 0;
	
	puts("Every item in the list should be 0");

	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
	
		while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
			for (i = 0;buffer[i] != '\0';i++)
				switch (buffer[i]) {
				case '\'':
					apostrophe = 1 - apostrophe;
					break;
				case '"':
					quote = 1 - quote;
					break;
				case '[':
					bracket++;
					break;
				case ']':
					bracket--;
					break;
				case '{':
					curly++;
					break;
				case '}':
					curly--;
					break;
				case '(':
					parenthesis++;
					break;
				case ')':
					parenthesis--;
					break;
				case '/':
					if (buffer[i + 1] == '*') {
						comment++;
						i++;
					}
					break;
				case '*':
					if (buffer[i + 1] == '/') {
						comment--;
						i++;
					}
					break;
				}
		}

		printf("\n%s:\nApostrophes:%lld\nBrackets:%lld\nCurly braces:%lld\nComments:%lld\nParenthesis:%lld\nQuotes:%lld\n", *argv, apostrophe, bracket, curly, comment, parenthesis, quote);
		apostrophe = bracket = curly = comment = parenthesis = quote = 0;
		fclose(fp);
	}
		
	return 0;
}
