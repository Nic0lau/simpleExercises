/* Line counter */

#include <stdio.h>

int
main()
{

	unsigned int lines, tabs, spaces, totalCh;
	int ch;
	
	lines = tabs = spaces = totalCh = 0;
	ch = getchar();

	while (ch != EOF) {
	
		switch(ch) {
		
		case '\n':
			lines++;
			break;
		case '\t':
			tabs++;
			break;
		case ' ' :
			spaces++;
			break;
		default:
			totalCh++;
			break;
		};	
		ch = getchar();
	};
	totalCh = totalCh + spaces + tabs + lines;
	printf("\nCharacters:%u\nLines:%u\nSpaces:%u\nTabs:%u\n", totalCh, lines, spaces, tabs);
	return 0;

};
