/* Two different ways of binary search */

#include <stdio.h>
#include <time.h>

int binSearch1(int x, int v[], int n);
int binSearch2(int x, int v[], int n);

int
binSearch1(int x, int v[], int n)
{
	int low, mid, high;
	
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

int
binSearch2(int x, int v[], int n)
{
	int low, mid, high;
	
	low = 0;
	high = n - 1;
	mid = (low + high) / 2;

	while(low <= high && x != v[mid]) {
		if (x < v[mid])
			high = mid -1;
		else
			low = mid + 1; 

		mid = (low + high) / 2;
	}

	if (x == v[mid])
		return mid;
	else
		return -1;
}

int
main()
{
	clock_t timeReq;
	int list[] = {2, 5, 10, 24, 36, 42, 45, 49, 51, 59, 69, 99, 104, 2096, 8092};
	int pos;

	timeReq = clock();
	pos = binSearch1(8092, list, 15);
	timeReq = (clock() - timeReq) / CLOCKS_PER_SEC;
	
	printf("\nPosition: %d\nTime:%Lf\n", pos, (long double)timeReq);

	timeReq = clock();
	pos = binSearch2(8092, list, 15);
	timeReq = (clock() - timeReq) / CLOCKS_PER_SEC;
	
	printf("\nPosition2: %d\nTime2: %Lf\n", pos, (long double)timeReq);

	return 0;
}
