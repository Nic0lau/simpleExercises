/* Program that print a list of files from cli arguments in pages */

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 40

int
main(int argc, char **argv)
{

	FILE *fp;
	const char *prog = argv[0];
	char c;
	unsigned short pos, argcOriginal, currentLine;

	if (argc < 2) {

		fprintf(stderr, "Usage: program [file list]\n");
		return 1;
	
	}

	for (argcOriginal = argc, pos = 0, argv++, argc--;argc > 0;argc--, argv++, pos = 0, currentLine = 1) {
	
		system("clear || cls");
		if ((fp = fopen(*argv, "r")) == NULL)
			perror(prog);
		
		printf("\t\t\t%s\n", *argv);

		while ((c = fgetc(fp)) != EOF) {
		
			if (pos < WIDTH && c != '\n') {
			
				putchar(c);
				pos++;
			
			} else {
			
				putchar('\n');
				if (c != '\n') {
					
					pos = 1;
					putchar(c);
				
				} else {
				
					pos = 0;
				
				}
			
				currentLine++;
			
			}
			
			if (currentLine == HEIGHT - 1) {
			
				pos = 0;
				printf("\n%d\n", argcOriginal - argc);
				getchar();
				system("clear || cls");
				printf("\t\t\t%s\n", *argv);
				currentLine = 1;
			
			}
		
		}
		
		printf("%d\n", argcOriginal - argc);
		getchar();
		fclose(fp);
	
	}

	return 0;

}
