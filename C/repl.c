/* Simple repl that can execute programs in PATH */
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 8192
#define MAX_ARG_AMOUNT 32

void
parse(char *line)
{
	char *args[MAX_ARG_AMOUNT] = {NULL};
	short unsigned i;
	
	args[0] = strtok(line, " ");
	for (i = 1;i < MAX_ARG_AMOUNT;i++) {
		args[i] = strtok(NULL, " ");
		if (args[i] == NULL)
			break;
	}
	
	if (fork() == 0) {
		if (execv(args[0], args) < 0) {
			perror("Error");
			exit(1);
		}
		exit(0);
	} else {
		wait(NULL);
	}
}

int
main()
{
	char line[MAX_LINE_SIZE] = {'\0'};
	
	while (1) {
		putchar('$');
		if (fgets(line, MAX_LINE_SIZE, stdin) == NULL)
			break;
		parse(line);
	}
	
	return 0;
}
