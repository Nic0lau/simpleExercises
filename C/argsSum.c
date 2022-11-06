/* Sum the command arguments */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	signed long long int somaTotal = 0;
	if (argc < 2) {
	
		puts("Argumentos insuficientes");
		return 1;
	};
	for(unsigned int c=1;c<argc;c++) {
	
		somaTotal += atoi(argv[c]);	
	
	};
	printf("%lli\n", somaTotal);
	return 0;

};
