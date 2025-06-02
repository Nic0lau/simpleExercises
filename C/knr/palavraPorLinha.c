/* Program that print every word from a file in a line */

#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

int
main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	FILE *fp;
	short unsigned i, n;
	
	if (argc < 2) {
		fputs("Usage:program [files]", stderr);
		return 1;
	}
	
	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
	
		while ((n = fread(buffer, 1, BUFFER_SIZE - 1, fp)) > 0)
			for (i = 0;i < n;i++)
				if (isspace(buffer[i]) && buffer[i] != '\n')
					putchar('\n');
				else
					putchar(buffer[i]);
		fclose(fp);
	}	
		
	return 0;
}
