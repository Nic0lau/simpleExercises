/* Program to print the lines where the words of a text appear */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 256
#define MAX_LINE_SIZE 8192
#define NOISE_WORD_AMOUNT 10

struct linkedList {
	short	unsigned data;
	struct	linkedList *next;
};

struct word {
	char	*word;
	struct	linkedList *lines;
	struct	word *left;
	struct	word *right;
};

short getWord(char *word, char *line);
short binSearch(char *word, const char **list, unsigned short size);
struct linkedList *insertLine(struct linkedList *root);
struct word *addWord(char *word, struct word *root);
void printBST(struct word *root);
void printLinkedList(struct linkedList *root);

long long unsigned currentLine = 1;
short unsigned lp = 0; /* Line pointer */
const char *noiseWords[NOISE_WORD_AMOUNT] = { 
    "A",
    "An",
    "And",
    "Or",
    "The",
    "a",
    "an",
    "and", 
    "or",
    "the"
};

short
getWord(char *word, char *line)
{
	char c;
	short unsigned j;
		
	while (!isalpha((c = line[lp++])) && c != EOF && c != '\0')
		if (c == '\n')
			currentLine++;

	if (c == EOF || c == '\0') {
		lp = 0;
		return EOF;
	}

	lp--;
		
	for (j = 0;isalpha(line[lp]);j++, lp++)
		word[j] = line[lp];

	word[j] = '\0';

	return word[0];
}

short
binSearch(char *word, const char **list, unsigned short size)
{
	short low, mid, high;
	
	low = 0;
	high = size - 1;

	while (low <= high) {	
		mid = (low + high) / 2;
		if (strcmp(word, list[mid]) < 0)
			high = mid - 1;
		else if (strcmp(word, list[mid]) > 0)
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

struct linkedList *
insertLine(struct linkedList *root)
{
	if (root == NULL) {
		root = (struct linkedList *) malloc(sizeof(struct linkedList));
		root->next = NULL;
		root->data = currentLine;
	} else if (root->data != currentLine) {
		root->next = insertLine(root->next);
	}

	return root;
}

struct word *
addWord(char *word, struct word *root)
{
	if (root == NULL) {
		root = (struct word *) malloc(sizeof(struct word));
		memset(root, 0, sizeof(struct word));
		root->word = strdup(word);
		root->lines = insertLine(root->lines);	
	} else if (strcmp(word, root->word) == 0) {
		root->lines = insertLine(root->lines);
	} else if (strcmp(word, root->word) < 0) {
		root->left = addWord(word, root->left);
	} else {
		root->right = addWord(word, root->right);	
	}
	
	return root;
}

void
printBST(struct word *root)
{
	if (root != NULL) {	
		printBST(root->left);
		printf("\n%s: ", root->word);
		printLinkedList(root->lines);
		printBST(root->right);
	}
}

void
printLinkedList(struct linkedList *root)
{
	struct linkedList *p;
	
	for (p = root;p != NULL;p = root->next)
		printf("%hu ", p->data);
}

int
main(int argc, char **argv)
{
	char word[MAX_WORD_SIZE] = {'\0'};
	FILE *fp;
	char line[MAX_LINE_SIZE] = {'\0'};
	struct word *root;
	
	if (argc < 2) {
		fputs("Usage: program [files]\n", stderr);
		return 1;
	}
	
	root = NULL;
		
	for (argv++, argc--;argc > 0;argv++, argc--) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
		
		while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
			while (getWord(word, line) != EOF)
				if (binSearch(word, noiseWords, NOISE_WORD_AMOUNT) < 0)
					root = addWord(word, root);
			
			line[lp] = '\0';
		}
	
		fclose(fp);
	}

	printBST(root);
	printf("\n");

	return 0;
}
