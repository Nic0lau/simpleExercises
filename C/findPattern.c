/* Program to search for keywords in a file */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 8192
#define MAX_WORD_SIZE 256

short getPattern(char *line, char *pattern);

short
getPattern(char *line, char *pattern)
{
	short unsigned i;
	char *p;

	for (p = line;*p != '\0';p++)
		if (*p == pattern[0]) {
		
			for (i = 0;*p == pattern[i] && pattern[i] != '\0';p++, i++);
				
			if (pattern[i] == '\0')
				return 0;
		}

	return -1;
}

int
main(int argc, char **argv)
{
	char line[MAX_LINE_SIZE] = {'\0'};
	FILE *fp;
	char *prog, *pattern;

	prog = argv[0];
	pattern = argv[1];
	
	if (argc < 3) {
		fputs("Usage: program [pattern] [files]\n", stderr);
		return 1;	
	}
	
	for (argv +=2, argc -= 2;argc > 0;argv++, argc--) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(prog);
			continue;
		}
		
		while (fgets(line, MAX_LINE_SIZE, fp) != NULL)
			if (getPattern(line, pattern) == 0)
				printf("%s:%s\n", *argv, line);
	
		fclose(fp);	
	}

	return 0;
}
