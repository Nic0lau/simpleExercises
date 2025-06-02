/* Program that replaces some words from a file with other words following a table */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8192
#define HASH_SIZE 128
#define MAX_DEST_FILE_NAME 64
#define MAX_WORD_SIZE 256
#define TABLE_LINE_SIZE 256
#define TABLE_ITEM_SIZE TABLE_LINE_SIZE / 2

struct macro {
	struct	macro *next;
	char	*original;
	char	*substitute;
};

short unsigned hashGen(char *s);
struct macro *search(char *s);
struct macro *append(char *original, char *substitute);
short removeMacro(char *original);
void printMacros(struct macro **list);
void parseTable(FILE *fp);
char getWord(char *word, char *buffer, FILE *fp);

short unsigned bp = 0; /* Buffer pointer */
static struct macro *hash[HASH_SIZE];

short unsigned
hashGen(char *s)
{
	int unsigned val;
	
	for (val = 5139;*s != 0;s++)
		val = *s + 42 * val;
	
	return val % HASH_SIZE;
}

struct macro *
search(char *s)
{
	struct macro *p;
	
	for (p = hash[hashGen(s)];p != NULL;p = p->next)
		if (strcmp(s, p->original) == 0)
			return p;
	
	return NULL;
}

struct macro *
append(char *original, char *substitute)
{
	struct macro *p;
	unsigned int hashVal;
	
	if ((p = search(original)) == NULL) {
		p = (struct macro *) malloc(sizeof(struct macro));
		
		if (p == NULL || (p->original = strdup(original)) == NULL)
			return NULL;
		
		hashVal = hashGen(original);
		p->next = hash[hashVal];
		hash[hashVal] = p;
	} else {
		free(p->substitute);
	}

	if ((p->substitute = strdup(substitute)) == NULL)
		return NULL;

	return p;
}

short
removeMacro(char *original)
{
	unsigned int hashVal;
	struct macro *p;
	
	if ((p = search(original)) != NULL) {
		hashVal = hashGen(original);
		hash[hashVal] = p->next;
		free(p);
		return 0;	
	}

	return -1;
}

void
printMacros(struct macro **list)
{
	short unsigned i;
	struct macro *p;
	
	for (i = 0;i < HASH_SIZE;i++, list++)
		if (*list != NULL)
			for(p = *list;p != NULL;p = p->next)
				printf("Original: %s\nSubstitute: %s\n", p->original, p->substitute);
}

void
parseTable(FILE *fp)
{
	char buffer[TABLE_LINE_SIZE] = {'\0'};
	short unsigned i, j;
	char original[TABLE_ITEM_SIZE] = {'\0'};
	char substitute[TABLE_ITEM_SIZE] = {'\0'};
	
	while (fgets(buffer, TABLE_LINE_SIZE, fp) != NULL) {
		for (i = 0;buffer[i] != '=';i++)
			original[i] = buffer[i];
		
		original[i] = '\0';
		
		for (j = 0, i++;buffer[i] != '\n' && buffer[i] != '\0';i++, j++)
			substitute[j] = buffer[i];
		
		substitute[j] = '\0';
		
		append(original, substitute);
		memset(buffer, 0, TABLE_LINE_SIZE);
	}
}

/* fp is where the characters out of words are stored */
char
getWord(char *word, char *buffer, FILE *fp)
{
	char c;
	short unsigned j;
	
	while (!isalpha((c = buffer[bp++])) && bp < BUFFER_SIZE && c != EOF)
		if (fputc(c, fp) == EOF)
			perror("fputc");

	if (c == EOF || bp >= BUFFER_SIZE) {
		bp = 0;
		return EOF;
	}
	
	bp--;
	
	for (j = 0;isalpha(buffer[bp]);j++, bp++)
		word[j] = buffer[bp];
	
	word[j] = '\0';
	
	return word[0];
}

int
main(int argc, char **argv)
{	
	char buffer[BUFFER_SIZE] = {'\0'};
	char destination[MAX_DEST_FILE_NAME] = {'\0'};
	FILE *fpa, *fpb;
	struct macro *p;
	char word[MAX_WORD_SIZE] = {'\0'};
	
	if (argc < 3) {
		fputs("Usage:program [table] [files]\n", stderr);
		return 1;
	}

	if ((fpa = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 1;
	}

	parseTable(fpa);
	printMacros(hash);

	for (argc -= 2, argv += 2;argc > 0;argc--, argv++) {
		if ((fpa = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
		
		strcpy(destination, *argv);
		
		if ((fpb = fopen(strcat(destination, "x"), "w")) == NULL) {
			perror(destination);
			continue;
		}
		
		while (fread(buffer, 1, BUFFER_SIZE, fpa) != 0) {
			while (getWord(word, buffer, fpb) != EOF) {
				if ((p = search(word)) != NULL) {
					if (fputs(p->substitute, fpb) < 0)
						perror("fputs");
				} else {
					if (fputs(word, fpb) < 0)
						perror("fputs");
				}
			}
			
			memset(buffer, 0, BUFFER_SIZE);
		}	
	
		fclose(fpa);
		fclose(fpb);
	}

	return 0;
}
