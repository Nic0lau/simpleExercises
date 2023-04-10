/* Program to sort the lines of a file */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 8192

struct line {
	char	*line;
	struct	line *left;
	struct	line *right;
};

int numcmp(const char *s1, const char *s2);
int strcmp_f(const char *s1, const char *s2);
struct line *addLine(struct line *root, char *line, int (*cmp)(const char *s1, const char *s2), short order);
void printBST(struct line *root);

int
numcmp(const char *s1, const char *s2)
{
	double x, y;
	
	x = atof(s1);
	y = atof(s2);	
	
	if (x > y)
		return 1;
	else if (x < y)
		return -1;
	else
		return 0;	
}

int
strcmp_f(const char *s1, const char *s2)
{
	for (;toupper(*s1) == toupper(*s2);s1++, s2++);
	
	return toupper(*s1) - toupper(*s2);
}

struct line *
addLine(struct line *root, char *line, int (*cmp)(const char *s1, const char *s2), short order)
{
	if (root == NULL) {
		root = (struct line *) malloc(sizeof(struct line));
		root->line = strdup(line);
		root->left = NULL;
		root->right = NULL;
	} else if ((*cmp)(line, root->line) * order < 0) {
		root->left = addLine(root->left, line, cmp, order);
	} else if ((*cmp)(line, root->line) * order > 0) {
		root->right = addLine(root->right, line, cmp, order);
	}

	return root;
}

void
printBST(struct line *root)
{
	if (root != NULL) {
		printBST(root->left);
		printf("%s", root->line);
		printBST(root->right);
	}
}

int
main(int argc, char **argv)
{
	FILE *fp;
	short unsigned i, isFold = 0, isNumeric = 0, isReverse = 0;
	char line[MAX_LINE_SIZE] = {'\0'};
	struct line *root = NULL;
	
	if (argc < 2) {
		fputs("Usage:program [-fnr] [files]\n", stderr);
		return 1;
	}
	
	if (argv[1][0] == '-') {
		for (i = 1;argv[1][i] != '\0';i++) {
			switch (argv[1][i]) {
			case 'n':
				isNumeric = 1;
				break;
			case 'r':
				isReverse = 1;
				break;
			case 'f':
				isFold = 1;
				break;
			default:
				printf("Error: unknown option %s", *argv);
				return -1;
			}
		}
		argv++;
		argc--;
	}

	for (argc--, argv++;argc > 0;argc--, argv++) {
		if ((fp = fopen(*argv, "r")) == NULL) {
			perror(*argv);
			continue;
		}
		
		while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
			root = addLine(root, line, (isNumeric) ? numcmp : 
			    (isFold) ? strcmp_f : strcmp, (isReverse) ? -1 : 1);
		}
	
		fclose(fp);
	}

	printBST(root);

	return 0;
}
