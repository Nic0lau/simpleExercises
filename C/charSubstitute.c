/* Transforming tabs in \t, backspaces in \b, and backslashes in \\ */

#include <stdio.h>

int
main()
{

	int ch;

	ch = getchar();

	while (ch != EOF) {
	
		switch(ch) {
		
		case '\t':
			printf("\\t");
			break;
		case '\\':
			printf("\\\\");
			break;
		case '\b' :
			printf("\\b");
			break;
		default:
			putchar(ch);
			break;
		};	
		ch = getchar();
	};
	return 0;

};
