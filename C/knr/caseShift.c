/* Function equivalent to the macro "tolower" from ctype header */

#include <stdio.h>

void
caseShift(char *text)
{
	short unsigned i;
	
	for (i = 0;text[i] != '\0';i++)
		text[i] = (text[i] >= 'A' && text[i] <= 'Z') ? text[i] + 32 : text[i];
}

int
main()
{
	char text[] = "ThE quIck bRown FOx jUMps ovEr The lazy DOG.";
	caseShift(text);
	printf("\n%s\n", text);
	return 0;
}
