/* Minimal re-implementation of printf */

#include <stdarg.h>
#include <stdio.h>

void myPrintf(char *format, ...);

void
myPrintf(char *format, ...)
{
	va_list ap;
	char *p;
	
	va_start(ap, format);

	for (p = format;*p != '\0';p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		
		switch (*++p) {
		case 'i':
		case 'd':
			printf("%d", va_arg(ap, int));
			break;
		case 'f':
			printf("%f", va_arg(ap, double));
			break;
		case 'p':
			printf("%p", va_arg(ap, void *));
			break;
		case 's':
			printf("%s", va_arg(ap, char *));
			break;
		case 'u':
			printf("%u", va_arg(ap, unsigned int));
			break;
		case 'x':
			printf("%x", va_arg(ap, unsigned int));
			break;
		case 'X':
			printf("%X", va_arg(ap, unsigned int));
			break;
		default:
			putchar(*p);
			break;
		}	
	}

	va_end(ap);
}

int
main()
{
	myPrintf("%d\n", 9);
	myPrintf("%x\n", ' ');
	
	return 0;
}
