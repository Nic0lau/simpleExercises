#include <stdio.h>

int main() {

		unsigned long long int a = 0;
		unsigned long long int b = 1;
		unsigned long long int c = a+b;
		unsigned short int escolha;

		puts("Você quer uma sequencia de fibonacci finita ou infinita?\n1-Finita\n2-Infinita");
		scanf("%hu", &escolha);
		if(escolha == 1) {
			unsigned short int limite;
			unsigned short int contador;
			puts("Você quer contar até qual numero da sequencia de fibonacci?");
			scanf("%hu", &limite);
			printf("\n%llu\n", a);
			printf("%llu\n", b);
			for(contador=1;contador<=(limite-2);contador++) {

				printf("%llu\n",c);
				a = b;
				b = c;
				c = a+b;

			}

		} else {

			printf("%llu\n", a);
			printf("%llu\n", b);
			while(1 == 1) {

				printf("%llu\n",c);
				a = b;
				b = c;
				c = a+b;

			}

		}
		return 0;
};
