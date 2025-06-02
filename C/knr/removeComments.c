/* Program to remove comments of a C code, with very naive implementation */

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define MAX_DEST_FILE_NAME 64

int
main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	char destination[MAX_DEST_FILE_NAME] = {'\0'};
	FILE *fpa, *fpb;
	short unsigned i, inQuote, inComment, n;
	
	if (argc < 2) {
		fputs("Usage:program [files]\n", stderr);
		return 1;
	}
	
	inQuote = inComment = 0;
	
	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fpa = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}

		strcpy(destination, *argv);
		strcat(destination, "x");
		
		if ((fpb = fopen(destination, "w")) == NULL) {
			perror(destination);
			continue;
		}

		while ((n = fread(buffer, 1, BUFFER_SIZE, fpa)) > 0) {
			for (i = 0;i < n;i++) { 
				if (buffer[i] == '"') {
					inQuote = 1 - inQuote; /* Invert value */
				} else if (buffer[i] == '/' && inQuote == 0) {
					if (buffer[i + 1] == '*')
						inComment = 1;
				} else if (buffer[i] == '*' && inComment == 1) {
					if (buffer[i + 1] == '/') {
						inComment = 0;
						i += 2;
					}	
				}
				if (inComment == 0)
					fputc(buffer[i], fpb);
			}
		}
	}
	
	return 0;
}
