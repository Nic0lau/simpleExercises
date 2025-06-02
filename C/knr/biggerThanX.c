/* Read file and print only ones bigger than a number of characters */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32768

typedef struct line {

	struct	line *next;
	char	*s;
	short	unsigned size;

} Line;

Line *add_line(char *s, Line *head);
void print_list(Line *head);

Line *
add_line(char *s, Line *head)
{
	if (head == NULL) {
		head = (Line *) malloc(sizeof(Line));
		head->next = NULL;
		head->s = strdup(s);
	} else if (strcmp(s, head->s) != 0) {
		head->next = add_line(s, head->next);
	}

	return head;
}

void
print_list(Line *head)
{
	if (head != NULL) {
		printf("%s", head->s);
		print_list(head->next);
	}
}

int
main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE];
	FILE *fp;
	Line *head;
	short min;

	if (argc < 2) {
		fprintf(stderr, "Usage: program [minimum line length] [files]");
		return 1;
	}
	
	head = NULL;

	/* Check for unspecified or negative minimum line length */
	if ((min = atoi(*++argv)) == 0 || min < 0) {
		min = 1;
	} else {
		argv++;
		argc--;
	}
	
	for (argc--;argc > 0;argc--, argv++) {
		if (strcmp("-", *argv) == 0) {
			fp = stdin;
		} else if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}

		while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
			if (strlen(buffer) > min)
				head = add_line(buffer, head);
		}
		
		if (fclose(fp) < 0)
			perror(*argv);
	}

	print_list(head);

	return 0;
}
