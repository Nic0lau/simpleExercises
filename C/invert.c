#include <stdio.h>

/* Reversing an array */

static void
arrayInvert(int array[], unsigned int arrayLength)
{

	int mid;
	int start;
	int end;
	
	start = 0;
	end = arrayLength - 1;
	
	while (start < end) {
	
		mid = array[start];
		array[start] = array[end];
		array[end] = mid;
	
		start++;
		end--;
	
	};

};

int
main()
{

	unsigned int i;
	int list[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	for (i = 0;i < 15;i++)
		printf("%d\n",list[i]);
	arrayInvert(list, 15);
	for (i = 0;i < 15;i++)
		printf("%d\n", list[i]);
	return 0;

};
