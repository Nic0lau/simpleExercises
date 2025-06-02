/* Reverting an array */
#include <stdio.h>

void
arrayInvert(int *array, short unsigned length)
{
	int tmp;
	short unsigned low;
	short unsigned high;
	
	low = 0;
	high = length - 1;
	
	while (low < high) {
		tmp = array[low];
		array[low] = array[high];
		array[high] = tmp;
	
		low++;
		high--;
	}
}

int
main()
{
	short unsigned i;
	int list[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	for (i = 0;i < 15;i++)
		printf("%d\n",list[i]);
	
	arrayInvert(list, 15);
	
	for (i = 0;i < 15;i++)
		printf("%d\n", list[i]);
	
	return 0;
}
