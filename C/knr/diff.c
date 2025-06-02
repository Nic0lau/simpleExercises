/* Program that print the lines where two files differ */

#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 8192

void
diff(FILE *fpa, FILE *fpb, char *namea, char *nameb)
{
	char buffer[MAX_LINE_SIZE];
	char buffer2[MAX_LINE_SIZE];
	
	while (fgets(buffer, MAX_LINE_SIZE, fpa) != NULL && fgets(buffer2, MAX_LINE_SIZE, fpb) != NULL)
		if (strcmp(buffer, buffer2) != 0)
			printf("%s:%s\n%s:%s\n", namea, buffer, nameb, buffer2);
}

int
main(int argc, char **argv)
{
	FILE *fpa;
	FILE *fpb;
	
	char *prog = argv[0];

	if (argc < 3) {
		fprintf(stderr, "Usage: program [file1] [file2]\n");
		return 1;
	}
	
	if ((fpa = fopen(*(argv + 1), "r")) == NULL || (fpb = fopen(*(argv + 2), "r")) == NULL) {
		perror(prog);
		return 1;
	} else {	
		diff(fpa, fpb, *(argv + 1), *(argv + 2));
	}
	
	return 0;
}
