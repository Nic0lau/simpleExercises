#include <stdio.h>
#include <string.h>
 
/* Function to swap values at two pointers */
void swap(char **v, int l, int r)
{
    char *temp;
    temp = v[l];
    v[l] = v[r];
    v[r] = temp;
}
 
void permute(char **a, int l, int r, FILE *fp)
{
    int i, j;
    if (l == r) {
    	for (j = 0;j < 12;j++)
    		if (j != 11)
    			fprintf(fp, "%s ", a[j]);
    		else
    			fprintf(fp, "%s", a[j]);
    	fputc('\n', fp);
    } else {
        for (i = l; i <= r; i++) {
            swap(a, l, i);
            permute(a, l + 1, r, fp);
            swap(a, l, i); // backtrack
        }
    }
}
 
int
main()
{
	FILE *fp;
	fp = fopen("lista.txt", "w");
	char *list[] = {
	    "speak",
    	    "scene",
            "vessel",
    	    "sand",
    	    "horn",
    	    "emotion",
    	    "play",
    	    "already",
    	    "bicycle",
    	    "fresh",
    	    "car",
    	    "settle"
    	};

	permute(list, 0, 11, fp);
	return 0;
}
