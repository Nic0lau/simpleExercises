/* Counting the spaces */

#include <stdio.h>

int
main()
{

	int ch;
	unsigned int spaceCounter;

	ch = getchar();
	spaceCounter = 0;
	
	while (ch != EOF) {

		if (ch == ' ') {

			spaceCounter++;
			if (spaceCounter == 1)
				putchar(ch);	
		
		} else {
		
			spaceCounter = 0;
			putchar(ch);
		
		}
		ch = getchar();
	
	}
	return 0;

};
