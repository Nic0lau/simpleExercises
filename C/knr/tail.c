/* My implementation of tail command */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
	char	*line;
	struct	line *next;
};

#define LINE_AMOUNT_DEFAULT 10
#define MAX_LINE_SIZE 8192

struct line *addLine(char *line, struct line *head);
void printTail(struct line *head, long long unsigned amount, long long unsigned total);
void freeList(struct line *head);

struct line *
addLine(char *line, struct line *head)
{
	if (head == NULL) {
		head = (struct line *) malloc(sizeof(struct line));
		head->line = strdup(line);
		head->next = NULL;
	} else {
		head->next = addLine(line, head->next);
	}
	
	return head;
}

void
printTail(struct line *head, long long unsigned amount, long long unsigned total)
{
	long long unsigned i;
	struct line *p;
	
	for (i = 0, p = head;i < (total - amount);i++, p = p->next);
	
	for (;amount > 0;amount--, p = p->next)
		printf("%s", p->line);
}

void
freeList(struct line *head)
{
	if (head->next != NULL)
		freeList(head->next);
	free(head->line);
	free(head->next);
}

int
main(int argc, char **argv)
{
	long long unsigned amount = LINE_AMOUNT_DEFAULT;
	char buffer[MAX_LINE_SIZE] = {'\0'};
	FILE *fp;
	struct line *head = NULL;
	long long unsigned totalLines = 0;

	if (argc < 2) {
		fputs("Usage:program [line amount] [files]\n", stderr);
		return 1;
	}
	
	if (isdigit(argv[1][0])) {
		amount = atoll(argv[1]);
		argc--;
		argv++;
	}

	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}

		while (fgets(buffer, MAX_LINE_SIZE, fp) != NULL) {
			head = addLine(buffer, head);
			totalLines++;
		}

		printTail(head, amount, totalLines);
		
		freeList(head);
		head = NULL;
		totalLines = 0;
		fclose(fp);		
	}	

	return 0;
}
