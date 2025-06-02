/* Re-implementation of cat command */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 64

int
main(int argc, char **argv)
{
	short fd;
	short n;
	char buffer[BUFFER_SIZE];
	
	if (argc == 1) {	
		fputs("Usage: program [files]\n", stderr);
		return 1;	
	}

	for (argv++, argc--; argc > 0;argc--, argv++) {	
		if ((fd = open(*argv, O_RDONLY)) < 0) {
			perror(*argv);
			continue;
		}
		
		while ((n = read(fd, buffer, BUFFER_SIZE)) > 0)
			write(1, buffer, n);

		if ((fd = close(fd)) < 0)
			perror(*argv);			
	}

	putchar('\n');
	return 0;
}
