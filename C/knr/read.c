#include <stdio.h>

int main(int argc, char *argv[]) {
	
	char ch;
	FILE *file = fopen(argv[1],"r");
	
	if(argc != 2) {
	
		puts("Insert one file!");
		return -1;
	
	}
	
	if(file == NULL) {
	
		perror("Error opening the file");
	
	} else {
	
		while((ch = fgetc(file)) != EOF)
			putchar(ch);		
		
		fclose(file);
	}

	return 0;

}
