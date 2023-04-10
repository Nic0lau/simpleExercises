/* Program to print the words from files in decreasing order of frequency */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 8192
#define MAX_WORD_SIZE 256

struct word {
	char	*word;
	short	unsigned counter;
	struct	word *next;
};

char getWord(char *word, char *line);
struct word *addWord(char *word, struct word *head);
void orderWords(struct word *head);
void printLinkedList(struct word *head);

static short unsigned pos;

char
getWord(char *word, char *line)
{
	char c;
	short unsigned i;

	while (!isalpha((c = line[pos++])) && c != EOF && c != '\0');

	if (c == '\0' || c == EOF) {
		pos = 0;
		return EOF;
	}
	
	pos--;
	
	for (i = 0;isalpha(line[pos]);pos++, i++)
		word[i] = line[pos];
	
	word[i] = '\0';
	
	return word[0];
}

struct word *
addWord(char *word, struct word *head)
{
	if (head == NULL) {
		head = (struct word *) malloc(sizeof(struct word));
		head->next = NULL;
		head->word = strdup(word);
		head->counter = 1;
	} else if (strcmp(word, head->word) == 0) {
		head->counter++;
	} else {
		head->next = addWord(word, head->next);	
	}

	return head;
}

void
orderWords(struct word *head)
{
	short swaped;
	struct word *current = head;
	struct word *next = current->next;
	short unsigned tmpn;
	char *tmps;
	
	if (current == NULL || next == NULL)
		return;
	
	do {
		swaped = 0;
		while (next != NULL) {	
			if (current->counter < next->counter) {
				swaped = 1;
			
				tmpn = current->counter;
				current->counter = next->counter;
				next->counter = tmpn;
				
				tmps = current->word;
				current->word = next->word;
				next->word = tmps;
			}
					
			current = current->next;
			next = current->next;
		}
	
		current = head;
		next = current->next;
	} while (swaped != 0);
}

void
printLinkedList(struct word *head)
{
	struct word *p;
	
	for (p = head;p->next != NULL;p = p->next)
	printf("%hu %s\n", p->counter, p->word);
}

int
main(int argc, char **argv)
{
	FILE *fp;
	struct word *head = NULL;
	char line[MAX_LINE_SIZE] = {'\0'};
	char word[MAX_WORD_SIZE] = {'\0'};

	if (argc < 2) {
		fputs("Usage:program [files]\n", stderr);
		return 1;
	}

	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
	
		while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
			while (getWord(word, line) != EOF)
				head = addWord(word, head);
			line[pos] = '\0';
		}

		fclose(fp);
	}

	orderWords(head);
	printLinkedList(head);

	return 0;
}
