/* Counts characters, tabs, spaces and lines*/

#include <stdio.h>

int
main(int argc, char **argv)
{
	long long unsigned lines, tabs, spaces, totalCh;
	char c;
	FILE *fp;
	
	if (argc != 2) {
		fprintf(stderr, "Usage: program [file]\n");
		return 1;
	}
	
	lines = tabs = spaces = totalCh = 0;
	if ((fp = fopen(*++argv, "r")) == NULL) {
		perror(*argv);
		return 1;
	}

	while ((c = fgetc(fp)) != EOF) {
		switch(c) {
		case '\n':
			lines++;
			break;
		case '\t':
			tabs++;
			break;
		case ' ':
			spaces++;
			break;
		default:
			totalCh++;
			break;
		}
	}
	
	fclose(fp);
	totalCh = totalCh + spaces + tabs + lines;
	printf("Characters:%llu\nLines:%llu\nSpaces:%llu\nTabs:%llu\n", totalCh, lines, spaces, tabs);
	return 0;
}
